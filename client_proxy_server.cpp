#include "client_proxy_server.h"

ProxyServer::ProxyServer(Socket &socket, Morph &morph,
        std::vector<std::string> &workspaces, std::mutex &m) :
        Proxy(socket), morph(morph), workspaces(workspaces), m(m) {
    this->serverSocket.connect();
    setFlag(false);
}

bool ProxyServer::sendCmdMessage(char command, std::string &strMessage) {
    if (getFlag())
        return false;
    else {
        message.setCommand(command);
        message.setMessage(strMessage.c_str());
        message.setLength(strMessage.size());
        setFlag(true);
        return true;
    }
}

void ProxyServer::sendCMDMessage() {
    this->send(message);
}

void ProxyServer::run() {
    while (!_interrupt) {
        if (getFlag()) {
            try {

                //Envio el mensaje al otro extremo de la comunicacion
                sendCMDMessage();

                //Recibo el resultado del mensaje enviado
                int s = receive();
                if (s == 0) {
                    finished = true;
                    break;
                }

                std::string mensajeRecibido;

                switch (message.getCommand()) {
                case ERRORMESSAGE: {
                    errorMsg = message.getMessage();
                    break;
                }
                case OK_MSG_MORPH: {
                    mensajeRecibido = message.getMessage();
                    m.lock();
                    ParserProtocoloMorph(morph, mensajeRecibido);
                    m.unlock();
                    break;
                }
                case OK_MSG_SELECT_WKS: {
                    mensajeRecibido = message.getMessage();
                    m.lock();
                    ParserProtocoloWorkspaces(workspaces,
                            mensajeRecibido);
                    m.unlock();
                    break;
                }
                default:
                    std::cerr << "Mensaje desconocido." << std::endl;
                    break;
                }

            } catch (const std::runtime_error &e) {
                if (!_interrupt)
                    throw e;
            }
            setFlag(false);
        }
    }
}

bool ProxyServer::getFlag() const {
    m.lock();
    bool _flag = flag;
    m.unlock();
    return _flag;
}

void ProxyServer::setFlag(const bool newValue) {
    m.lock();
    flag = newValue;
    m.unlock();
}

bool ProxyServer::areThereErrors() const {
    return (errorMsg.size() > 0);
}

std::string ProxyServer::getErrors() {
    std::string copy = errorMsg;
    errorMsg.clear();
    return copy;
}

