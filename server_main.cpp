#include <iostream>
#include <fstream>

#include "server_accepter.h"
#include "server_server.h"

#define SERVER_PARAMS 3
const char* SERVER_MODE_SERVER = "s";
const char* SERVER_MODE_FILE = "f";
#define RET_OK 0
#define RET_NOK 1

#include "server_mode_selector.h"

int main(int argc, char **argv) {
    try {
        if (argc == SERVER_PARAMS) {
            char* mode = *(argv + 1);
            if (strcmp(mode, SERVER_MODE_SERVER) == 0) {
                int port = 0;
                try {
                    port = std::stoi(*(argv + 2));
                } catch (...) {
                    throw std::runtime_error("puerto invalido.");
                }
                ModeSelector modeSelector(port);
            } else if (strcmp(mode, SERVER_MODE_FILE) == 0) {
                std::string filename = std::string(*(argv + 2));
                ModeSelector modeSelector(filename);
            } else {
                std::cerr << "Forma de uso: >>> ./server <modo s|f> <port|file>"
                        << std::endl;
            }
        } else {
            std::cerr << "Forma de uso: >>> ./server <modo s|f> <port|file>"
                    << std::endl;
            return RET_NOK;
        }
    } catch (const std::runtime_error &e) {
        std::cout << "Error. " << std::endl << e.what() << std::endl;
    } catch (...) {
        std::cout << "Error desconocido." << std::endl << std::endl;
    }
    return RET_OK;
}
