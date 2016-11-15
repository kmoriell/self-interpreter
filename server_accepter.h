/*
 * server_accepter.h
 *
 *  Created on: 22 de set. de 2016
 *      Author: kmoriell
 */

#ifndef SERVER_ACCEPTER_H_
#define SERVER_ACCEPTER_H_

#include "common_socket.h"
#include <stdexcept>
#include <vector>

#include "server_proxyClient.h"
#include "common_thread.h"
#include "server_server.h"
#include "server_workspace.h"

class Accepter: public Thread {
private:
	std::vector<ProxyClient*> program_threads;
	Server &server;
	Workspace* workspace;
	Socket socket;
	bool interrupt_task;

public:
	/// Constructor
	/**
	 * @param port puerto donde escuchar
	 * @param server referencia al Server
	 * @param workspace  puntero a Workspace.
	 */
	Accepter(uint32_t port, Server &server, Workspace *workspace);

	/// Destructor
	~Accepter();

	/** Metodo que sirve para la interrupcion del proceso.
	 *
	 */
	void interrupt();

	/** Metodo principal de la clase. Hace los procesamientos
	 *
	 */
	virtual void run();

	/** Revisa si los clientes que tiene conectados terminaron su ejecucion,
	 * luego limpia los recursos utilizados
	 *
	 */
	void collect_closed_clients();
};

#endif /* SERVER_ACCEPTER_H_ */
