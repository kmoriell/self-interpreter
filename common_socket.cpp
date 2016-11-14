/*
 * socket.c
 *
 *  Created on: 21 de set. de 2016
 *      Author: kmoriell
 */

#include "common_socket.h"
#include <string>

Socket::Socket(std::string hostname, uint32_t port) {
	this->socket_fd = 0;
	this->ptr = nullptr;
	this->port = port;
	this->hostname = hostname;
	this->_shutdown = false;
	this->accepted_socket_fd = 0;
	initialize(0);
}

Socket::Socket(uint32_t port) {
	this->socket_fd = 0;
	this->ptr = nullptr;
	this->port = port;
	this->_shutdown = false;
	this->accepted_socket_fd = 0;
	initialize(AI_PASSIVE);
}

Socket::Socket(const Socket &sck) {
	this->ptr = nullptr;
	this->accepted_socket_fd = 0;
	this->_shutdown = false;
	this->port = sck.port;
	this->socket_fd = sck.accepted_socket_fd;
}

Socket::~Socket() {
	shutdown();
}

void Socket::initialize(uint32_t flags) {
	std::memset(&hints, 0, sizeof(struct addrinfo));
	std::memset(&addr, 0, sizeof(struct addrinfo));

	hints.ai_family = AF_INET; /* IPv4 (or AF_INET6 for IPv6)     */
	hints.ai_socktype = SOCK_STREAM; /* TCP  (or SOCK_DGRAM for UDP)    */
	hints.ai_flags = flags;

	std::string __port = std::to_string(port);
	int s = ::getaddrinfo(NULL, __port.c_str(), &hints, &ptr);
	if (s < 0)
		throw std::runtime_error("Error en la llamada a getaddrinfo.");

	this->socket_fd = ::socket(ptr->ai_family, ptr->ai_socktype,
			ptr->ai_protocol);

	if (this->socket_fd < 0) {
		freeaddrinfo(ptr);
		throw std::runtime_error("No se pudo crear el socket.");
	}

	if (!flags) {
		int val = 1;
		s = setsockopt(this->socket_fd, SOL_SOCKET, SO_REUSEADDR, &val,
				sizeof(val));

		if (s < 0) {
			freeaddrinfo(ptr);
			throw std::runtime_error("Error en la llamada a setsockopt");
		}
	}
}

Socket* Socket::accept() {
	accepted_socket_fd = ::accept(this->socket_fd, NULL, NULL);
	if (accepted_socket_fd < 0) {
		std::string error("Error en la llamada a accept().\nError: ");
		std::string error_description(::strerror(errno));
		error += error_description;
		throw std::runtime_error(error);
	}

	Socket *sck = new Socket(*this);
	return sck;
}

int Socket::receive(char *buffer, uint32_t length) {
	uint32_t received = 0;
	int s = 0;
	bool valid = true;
	while (received < length && valid) {
		s = ::recv(this->socket_fd, &buffer[received], length - received,
		MSG_NOSIGNAL);
		if (s < 0) {
			std::string error("Error en la llamada a recv().\nError: ");
			std::string error_description(::strerror(errno));
			error += error_description;
			throw std::runtime_error(error);
		} else if (s == 0) {
			valid = false;
		} else {
			received += s;
		}
	}
	return s;
}

void Socket::connect() {
	struct addrinfo *result;

	bool connected = false;
	this->port = port;

	for (result = ptr; result != NULL && connected == false;
			result = result->ai_next) {
		if (this->socket_fd == -1) {
		} else {
			int s = ::connect(this->socket_fd, result->ai_addr,
					result->ai_addrlen);
			if (s == -1) {
				close(this->socket_fd);
				throw std::runtime_error("Error en la llamada a connect().");
			}
			connected = (s != -1);  // nos conectamos?
		}
	}
// libero la lista de direcciones
	freeaddrinfo(result);
}

void Socket::shutdown() {
	if (ptr) {
		freeaddrinfo(ptr);
		ptr = nullptr;
	}
	if (!_shutdown) {
		::shutdown(this->socket_fd, SHUT_RDWR);
		::close(this->socket_fd);
		_shutdown = true;
	}
}

void Socket::send(const char *buffer, uint32_t length) {
	int s = 0;
	uint32_t sent = 0;
	int valid = true;
	while (sent < length && valid) {
		s = ::send(this->socket_fd, &buffer[sent], length - sent, MSG_NOSIGNAL);
		if (s < 0) {  // error inesperado
			throw std::runtime_error("Error en la llamada a send().");
		} else if (s == 0) {
			valid = false;
		} else {
			sent += s;
		}
	}
}

void Socket::bind_and_listen() {
	int s = ::bind(this->socket_fd, ptr->ai_addr, ptr->ai_addrlen);

	if (s < 0) {
		std::string error("Error en la llamada a bind().\nError: ");
		std::string error_description(::strerror(errno));
		error += error_description;
		throw std::runtime_error(error);
	}

	// Puedo mantener en espera 10 clientes antes de aceptarlos
	s = ::listen(this->socket_fd, 10);

	if (s < 0) {
		std::string error("Error en la llamada a listen().\nError: ");
		std::string error_description(::strerror(errno));
		error += error_description;
		throw std::runtime_error(error);
	}
}
