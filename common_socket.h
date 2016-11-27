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
    // Constructores
    Socket(std::string hostname, uint32_t port);
    explicit Socket(uint32_t port);
    Socket(const Socket&);

    // Destructor
    ~Socket();

    // Metodo que sirve para escuchar en un determinado puerto
    void bind_and_listen();

    // Metodo que se usa para conectar un cliente a un servidor.
    void connect();

    // Metodo que sirve para aceptar un nuevo cliente. Devuelve un puntero
    // a Socket.
    Socket* accept();

    // Metodo que sirve para enviar un mensaje. Recibe un buffer y la longitud.
    void send(const char *buffer, uint32_t length);

    // Metodo que sirve para recibir un mensaje. Recibe un buffer y la longitud.
    int receive(char *buffer, uint32_t length);

    // Cierra el socket y libera los recursos.
    void shutdown();

    // Deshabilito  operador de asignacion
    Socket& operator=(const Socket&) = delete;
};

#endif /* COMMON_SOCKET_H_ */
