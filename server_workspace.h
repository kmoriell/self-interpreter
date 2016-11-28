#ifndef SERVER_WORKSPACE_H_
#define SERVER_WORKSPACE_H_

#include "server_object.h"
#include "server_parser.h"
#include "server_virtualMachine.h"
#include <string>
#include <iostream>

/** Representa un ambiente de trabajo (workspace) y es el encargado de crear
 * el lobby y de llamar al parser para ejecutar los scripts de código self.
 *
 */
class Workspace {
private:
    Object *lobby;
    VirtualMachine vm;

public:
    /// Constructor
    Workspace();

    Workspace(const Workspace&) = delete;
    Workspace(Workspace&&) = delete;

    Workspace& operator=(const Workspace&) = delete;
    Workspace& operator=(Workspace&&) = delete;

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

    /** Busca el objeto por ID y retorna el objeto real.
     * @param id id del objeto.
     *
     */
    Object* findObjectById(uint32_t id);
};

#endif /* SERVER_WORKSPACE_H_ */
