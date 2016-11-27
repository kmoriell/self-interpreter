#include "server_accepter.h"

#include <stdexcept>
#include <iostream>
#include <vector>

Accepter::Accepter(uint32_t port, Server &server) :
        program_threads(), server(server), socket(port) {
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
            //collect_closed_clients();
            ProxyClient *newProxy = new ProxyClient(*sck, server);
            program_threads.push_back(newProxy);
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
    for (uint32_t i = 0; i < program_threads.size(); i++) {
        program_threads[i]->interrupt();
        program_threads[i]->join();
        delete program_threads[i];
    }
}

void Accepter::collect_closed_clients() {
    std::vector<ProxyClient*> new_program_threads;

    for (uint32_t i = 0; i < program_threads.size(); i++) {
        if (program_threads[i]->is_finished()) {
            program_threads[i]->join();
            delete program_threads[i];
        } else {
            new_program_threads.push_back(program_threads[i]);
        }
    }

    new_program_threads.swap(program_threads);
    new_program_threads.clear();
}

