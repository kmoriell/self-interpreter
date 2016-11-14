#ifndef CLIENT_PROXYSERVER_H_
#define CLIENT_PROXYSERVER_H_

#include "common_socket.h"
#include "common_proxy.h"
#include "client_morph.h"
#include "client_parserProtocoloCliente.h"
#include "common_define.h"

class ProxyServer: public Proxy {
private:
	Socket socket;
	Morph &morph;
	//Este flag le indica al proxy que debe ejecutar un comando.
	bool flag;

public:
	ProxyServer(std::string hostname, uint32_t port, Morph& morph) :
			socket(hostname, port), Proxy(socket), morph(morph) {
		this->serverSocket.connect();
		this->flag = false;
		//this->command = ERRORMESSAGE;
		//this->message = "";
	}

	bool sendCmdMessage(char command, std::string &message) {
		if (flag)
			return false;
		else {
			morph.clear();
			std::cout << "comando a enviar: " << command << std::endl;
			std::cout << "mensaje a enviar: " << message << std::endl;
			clientMessage.setCommand(command);
			clientMessage.setMessage(message.c_str());
			clientMessage.setLength(message.size());
			this->flag = true;
			return true;
		}
	}

	virtual void sendCMDMessage() {
		this->send(clientMessage);
	}

	void run() {
		while (!_interrupt) {
			if (flag) {
				try {
					//Envio el mensaje al servidor
					sendCMDMessage();

					//Recibo el resultado del mensaje enviado
					int s = receive();
					if (s == 0) {
						finished = true;
						break;
					}

					std::string mensajeRecibido;

					switch (clientMessage.getCommand()) {
					case ERRORMESSAGE:
						std::cout << "El servidor devolvio error." << std::endl;
						break;
					case OKMESSAGE:
						std::cout << "Se recibio un mensaje OK" << std::endl;
						mensajeRecibido = clientMessage.getMessage();
						ParserProtocoloCliente parser(morph, mensajeRecibido);
						morph.mostrar();
						break;
					}

				} catch (const std::runtime_error &e) {
					if (!_interrupt)
						throw e;
				}
				flag = false;
			}
		}
	}
};

#endif /* CLIENT_PROXYSERVER_H_ */
