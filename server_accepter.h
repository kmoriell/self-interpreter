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
    Socket socket;
    bool interrupt_task;

public:
    /// Constructor
    /**
     * @param port puerto donde escuchar
     * @param server referencia al Server
     * @param workspace  puntero a Workspace.
     */
    Accepter(uint32_t port, Server &server);

    /** Constructor por copia deshabilitado
     *
     */
    Accepter(const Accepter&) = delete;

    /** Constructor por moviemiento deshabilitado
     *
     */
    Accepter(Accepter&&) = delete;

    /** Operador asignacion deshabilitado
     *
     */
    Accepter& operator=(const Accepter&) = delete;

    /** Operador asignacion por moviemiento deshabilitado
     *
     */
    Accepter& operator=(Accepter&&) = delete;

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
