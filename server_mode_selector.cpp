#include "server_mode_selector.h"
#include "server_workspace.h"

ModeSelector::ModeSelector(int port) {
    try {
        Server server;
        Accepter *accepter = new Accepter(port, server);
        // Este hilo va a estar corriendo durante toda la ejecucion del programa
        accepter->start();

        char c = '\0';
        while (c != SERVER_QUIT_CHAR) {
            std::cin.get(c);
        }
        exitRoutine(accepter);
        delete accepter;
    } catch (const std::runtime_error &e) {
        std::cout << "Error. " << std::endl << e.what() << std::endl;
    } catch (...) {
        std::cout << "Error desconocido." << std::endl << std::endl;
    }
}

ModeSelector::ModeSelector(std::string filename) {
    Workspace workspace;

    std::ifstream filein(filename);

    if (!filein.is_open())
        throw std::runtime_error("No se pudo abrir el archivo.");

    std::string script, x;
    while (filein >> x)
        script += x + " ";

    std::cout << script << std::endl;
    workspace.receive(workspace.getLobby(), script);
}

void ModeSelector::exitRoutine(Accepter* accepter) {
    // mando la señal para interrumpir el aceptador de conexiones
    accepter->interrupt();
    accepter->join();
}
