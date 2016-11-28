#include <iostream>
#include <fstream>
#include <unistd.h>
#include <vector>
#include <string>
#include <mutex>
#include "client_proxyServer.h"

#define CLIENT_PARAMS 3
#define RET_OK 0
#define RET_NOK 1

#include "client_selectWkWindow.h"

int main(int argc, char **argv) {
    try {
        if (argc != 4) {
            std::cout << "Argumentos: >>> .\\client <serverIP> <puerto>."
                    << std::endl;
            return RET_NOK;
        }

        std::mutex m;
        std::string server = argv[1];
        uint32_t port = 0;
        try {
            port = std::stoi(*(argv + 2));
        } catch (...) {
            throw std::runtime_error("puerto invalido.");
        }

        Morph morph;
        std::vector<std::string> workspaces;
        Socket socket(server, port);
        ProxyServer proxyServer(socket, morph, workspaces, m);

        //Aca se abrio un hilo nuevo que es del proxy
        proxyServer.start();

        auto app = Gtk::Application::create();
        SelectWkWindow window(morph, workspaces, proxyServer, m);
        app->run(*window.getWindow());

        proxyServer.interrupt();
        proxyServer.join();
    } catch (const std::runtime_error &e) {
        std::cout << "Error. " << std::endl << e.what() << std::endl;
    } catch (...) {
        std::cout << "Error desconocido." << std::endl << std::endl;
    }
    return RET_OK;
}
