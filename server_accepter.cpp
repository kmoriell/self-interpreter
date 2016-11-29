#include "server_accepter.h"
#include <stdexcept>
#include <vector>

Accepter::Accepter(uint32_t port, Server &server) :
        programThreads(), server(server), socket(port) {
    interrupt_task = false;
    socket.bind_and_listen();
}

Accepter::~Accepter() {
    socket.shutdown();
}

void Accepter::run() {
    try {
        while (!interrupt_task) {
            Socket *sck = socket.accept();
            collectClosedClients();
            ProxyClient *newProxy = new ProxyClient(*sck, server);
            programThreads.push_back(newProxy);
            newProxy->start();
        }
    } catch (const std::runtime_error &e) {
        if (!interrupt_task)
            throw e;
    }
}

void Accepter::interrupt() {
    this->interrupt_task = true;
    this->socket.shutdown();
    for (uint32_t i = 0; i < programThreads.size(); i++) {
        programThreads[i]->interrupt();
        programThreads[i]->join();
        delete programThreads[i];
    }
}

void Accepter::collectClosedClients() {
    std::vector<ProxyClient*> new_programThreads;

    for (uint32_t i = 0; i < programThreads.size(); i++) {
        if (programThreads[i]->is_finished()) {
            programThreads[i]->join();
            delete programThreads[i];
        } else {
            new_programThreads.push_back(programThreads[i]);
        }
    }

    new_programThreads.swap(programThreads);
    new_programThreads.clear();
}

