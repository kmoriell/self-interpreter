#ifndef COMMON_PROXY_H_
#define COMMON_PROXY_H_

#include "common_socket.h"
#include "common_thread.h"
#include "common_types.h"
#include "common_define.h"
#include "server_server.h"
#include "server_object.h"
#include <string>
#include <vector>

class Proxy : public Thread {
public:
	/** Constructor.
	 * @param socket socket sobre el cual trabajar
	 */
	Proxy(Socket &socket);

	/** Indica si la conexion finalizo.
	 *
	 */
	bool is_finished();

	/** Interrumpida la ejecucion del proxy.
	 *
	 */
	void interrupt();

protected:
	Socket &serverSocket;
	//Workspace *workspace = nullptr;
	bool _interrupt;
	bool finished;
	command_t clientMessage;

	/*void loadWorkspace(std::string name);
	 void availableWorkspace();
	 void newWorkspace(std::string name);
	 void closeWorkspace(std::string name);
	 void deleteWorkspace(std::string name);*/
	//virtual void sendCMDMessage() = 0;

	/** Envia un mensaje
	 * @message del tipo command_t con el mensaje
	 */
	void send(command_t &message);

	/** Recibe datos. Una vez que recibe los datos los guarda
	 * internamente.
	 *
	 */
	virtual int receive();

	/** Envia un mensaje de error
	 * @param msg std::string con el mensaje a enviar con la descripcion
	 * del error
	 */
	void sendError(std::string msg);

	/** Envia un mensaje de OK
	 * @param msg con el resultado de la operacion.
	 */
	void sendOK(std::string msg);
};

#endif /* COMMON_PROXY_H_ */
