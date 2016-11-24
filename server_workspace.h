#ifndef SERVER_WORKSPACE_H_
#define SERVER_WORKSPACE_H_

#include "server_object.h"
#include "server_parser.h"
#include "server_virtualMachine.h"
#include <string>
#include <iostream>

class Workspace {
private:
	Object *lobby;
	std::string selfInstr;
	VirtualMachine vm;

public:
	/// Constructor
	Workspace();

	/// Destructor
	~Workspace();

	/** Recibe codigo self y lo ejecuta.
	 * @param code [std::string] codigo que recibe
	 * @return Devuelve un Object* con el resultado de la ejecucion
	 *
	 */
	uint32_t receive(Object* context, std::string &code);

	/// Devuelve el objeto lobby.
	Object* getLobby();

	Object* findObjectById(uint32_t id);
};

#endif /* SERVER_WORKSPACE_H_ */
