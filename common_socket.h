#ifndef COMMON_SOCKET_H_
#define COMMON_SOCKET_H_

#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200112L
#endif

#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <stdexcept>

/** Representa una encapsulacion de los sockets provistos
 * por el sistema operativo que estan en las librerias de Unix.
 *
 */
class Socket {
private:
    std::string hostname;
    uint32_t port;
    int socket_fd;
    int accepted_socket_fd;
    struct addrinfo hints;
    struct addrinfo addr;
    struct addrinfo *ptr;
    void initialize(uint32_t flags);
    bool _shutdown;

public:
    /** Constructor
     * @param hostname IP del servidor
     * @param port puerto a escuchar
     */
    Socket(std::string hostname, uint32_t port);

    /** Constructor
     * @param port puerto a escuchar
     */
    explicit Socket(uint32_t port);

    /// Constructor por copia
    Socket(const Socket&);

    /// Destructor
    ~Socket();

    /// Metodo que sirve para escuchar en un determinado puerto
    void bind_and_listen();

    /// Metodo que se usa para conectar un cliente a un servidor.
    void connect();

    /* Metodo que sirve para aceptar un nuevo cliente. Devuelve un puntero
     * a Socket.
     */
    Socket* accept();

    /** Metodo que sirve para enviar un mensaje
     * @param buffer desde donde leer los datos a enviar
     * @param length tamanio en bytes de los datos a enviar
     */
    void send(const char *buffer, uint32_t length);

    /** Metodo que sirve para recibir un mensaje
     * @param buffer donde guardar los datos recibidos
     * @param length tamanio en bytes recibidos
     */
    int receive(char *buffer, uint32_t length);

    /// Cierra el socket y libera los recursos.
    void shutdown();

    /// Operador de asignacion deshabilitado
    Socket& operator=(const Socket&) = delete;
};

#endif /* COMMON_SOCKET_H_ */
