#include "server_modeSelector.h"
#include "server_workspace.h"

ModeSelector::ModeSelector(int port) {
	try {
		Server server;
		Accepter *connectionsAccepter = new Accepter(port, server);
		// Este hilo va a estar corriendo durante toda la ejecucion del programa
		connectionsAccepter->start();

		char c = '\0';
		while (c != SERVER_QUIT_CHAR) {
			std::cin.get(c);
		}
		exitRoutine (connectionsAccepter);
		delete connectionsAccepter;
	} catch (const std::runtime_error &e) {
		std::cout << "Error. " << std::endl << e.what() << std::endl;
	} catch (...) {
		std::cout << "Error desconocido." << std::endl << std::endl;
	}
}

ModeSelector::ModeSelector(std::string filename) {
	Workspace workspace;

	std::ifstream filein(filename);
	std::string script, x;
	while (filein >> x)
		script += x + " ";

	std::cout << script << std::endl;
	workspace.receive(workspace.getLobby(), script);

}

ModeSelector::~ModeSelector() {
	// TODO Auto-generated destructor stub
}

void ModeSelector::exitRoutine(Accepter* connectionsAccepter) {
	// mando la señal para interrumpir el aceptador de conexiones
	connectionsAccepter->interrupt();
	connectionsAccepter->join();
}
