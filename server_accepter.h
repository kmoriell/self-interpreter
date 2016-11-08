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

#include "common_thread.h"
#include "server_proxyClient.h"
#include "server_server.h"

class Accepter : public Thread {
 private:
  std::vector<ProxyClient *> program_threads;
  Server &server;
  Socket socket;
  bool interrupt_task;

 public:
  // Constructor. Recibe el puerto donde escuchar y una referencia al modelo
  Accepter(uint32_t port, Server &server);

  // Destructor
  ~Accepter();

  // Metodo que sirve para la interrupcion del proceso.
  void interrupt();

  // Metodo principal de la clase. Hace los procesamientos
  virtual void process();

  // Revisa si los clientes que tiene conectados termino su ejecucion.
  // Limpia los recursos utilizados.
  void collect_closed_clients();
};



#endif /* SERVER_ACCEPTER_H_ */
