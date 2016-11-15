#ifndef CLIENT_PROXYSERVER_H_
#define CLIENT_PROXYSERVER_H_

#include "common_socket.h"
#include "common_proxy.h"
#include "client_morph.h"
#include "client_parserProtocoloCliente.h"
#include "common_define.h"

class ProxyServer: public Proxy {
private:
	Socket socket;
	Morph &morph;
	//Este flag le indica al proxy que debe ejecutar un comando.
	bool flag;
	std::string errorMsg;
public:
	/** Constructor
	 * @param hostname std::string con el nombre del host a conectarse
	 * @papram port uint32_t con el puerto a conectarse
	 * @param morph, Morph que procesa los datos para luego mostrarlos por pantalla
	 */
	ProxyServer(std::string hostname, uint32_t port, Morph& morph);

	/** Envia un mensaje para ejecutar codigo self
	 * @command, char con el comando a ejecutar
	 * @message std::string con el mensaje a ejecutar
	 */
	bool sendCmdMessage(char command, std::string &message);


	virtual void sendCMDMessage();

	/** Metodo que sirve para
	 *
	 */
	void run();

	/** Obtiene el flag que determina que envio el comando y
	 * recibio la respuesta por parte del servidor. Indica
	 * que ya se concretaron las operaciones y que se puede
	 * volver a enviar nuevamente.
	 */
	bool getFlag() const;

	/** Indica si hubo errores o no informados por el servidor.
	 *
	 */
	bool areThereErrors() const;

	/** Obtiene los errores. Si no hubo ninguno devuelve una cadena vacio, si
	 * hay devuelve el error.
	 *
	 */
	std::string getErrors();
};

#endif /* CLIENT_PROXYSERVER_H_ */
