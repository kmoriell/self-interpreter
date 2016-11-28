#include <iostream>
#include <fstream>
#include <unistd.h>
#include <vector>
#include <string>
#include <mutex>
#include "client_proxyServer.h"

#define CLIENT_PARAMS 4
#define RET_OK 0
#define RET_NOK 1

#define SOLOGUI

#ifdef SOLOGUI
#include "client_selectWkWindow.h"
#endif

int main(int argc, char **argv) {
    if (argc != 4) {
        std::cout << "Argumentos: >>> .\\client <serverIP> <puerto> <archivo>."
                << std::endl;
        return 1;
    }

    std::mutex m;
    std::string server = argv[1];
    std::string _port = argv[2];
    uint32_t port = stoi(_port);
    std::ifstream filein(argv[3]);

    std::string script, x;

    while (filein >> x)
        script += x + " ";

    Morph morph;
    std::vector<std::string> workspaces;
    Socket socket(server, port);
    ProxyServer proxyServer(socket, morph, workspaces, m);

    //Aca se abrio un hilo nuevo que es del proxy
    proxyServer.start();
    std::cout << "Se abre un hilo para el proxyServer." << std::endl;
    std::cout << "Seteamos el flag." << std::endl;
#ifdef SOLOGUI
    auto app = Gtk::Application::create();
    SelectWkWindow window(morph, workspaces, proxyServer, m);
    app->run(*window.getWindow());
#else
    std::string message = script;
    std::cout << "script: " << script << std::endl;
    proxyServer.sendCmdMessage(EXEC_LOBBY_CMD, message);
    sleep(2);

    morph.mostrar();
    char __char;
    std::cin >> __char;
#endif

    proxyServer.interrupt();
    proxyServer.join();
    std::cout << "JOIN." << std::endl;
    std::cout << "SALIMOS." << std::endl;
    return 0;
}
