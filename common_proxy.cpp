#include "common_proxy.h"
#include <iostream>

Proxy::Proxy(Socket &socket) :
        serverSocket(socket) {
    finished = false;
    _interrupt = false;
}

int Proxy::receive() {
    char *strLen = new char[sizeof(int)];
    memset(strLen, 0, sizeof(int));

    int s = serverSocket.receive(strLen, sizeof(int));
    unsigned int len = 0;
    memcpy(&len, strLen, sizeof(int));
    len = ntohl(len);

    char command;
    s = serverSocket.receive(&command, sizeof(char));

    char *strMessage = new char[len + 1];
    serverSocket.receive(strMessage, len);
    strMessage[len] = '\0';

    message.setLength(len);
    message.setCommand(command);
    message.setMessage(strMessage);

    delete[] strMessage;
    delete[] strLen;
    return s;
}

void Proxy::send(command_t &response) {
    char command = response.getCommand();

    unsigned int len = response.getLength();
    len = htonl(len);

    char *strLen = new char[sizeof(int)];
    memcpy(strLen, &len, sizeof(int));

    std::cout << "send()" << std::endl;
    std::cout << "len = " << ntohl(len) << std::endl << " command = " << command
            << std::endl << " message = " << response.getMessage() << std::endl
            << std::endl;

    this->serverSocket.send(strLen, sizeof(int));
    this->serverSocket.send(&command, sizeof(char));
    this->serverSocket.send(response.getMessage().c_str(),
            response.getMessage().size());
    delete[] strLen;
}

void Proxy::sendError(std::string msg) {
    command_t response(msg.size(), ERRORMESSAGE, msg);
    send(response);
}

void Proxy::sendOK(std::string msg) {
    command_t response(msg.size(), OK_MSG_MORPH, msg);
    send(response);
}

void Proxy::sendOKWks(std::string msg) {
    command_t response(msg.size(), OK_MSG_SELECT_WKS, msg);
    send(response);
}

bool Proxy::is_finished() {
    return this->finished;
}

void Proxy::interrupt() {
    this->_interrupt = true;
    serverSocket.shutdown();
}

