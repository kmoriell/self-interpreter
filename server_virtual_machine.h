#ifndef SERVER_VIRTUALMACHINE_H_
#define SERVER_VIRTUALMACHINE_H_

#include <stack>
#include "server_object.h"

/** Es la encargada de crear y almacenarlos en una pila en el objeto lobby.
 * Tanto la maquina virtual como el objeto lobby son unicos por workspace.
 *
 */
class VirtualMachine {
private:
    Object* lobby = nullptr;

public:
    VirtualMachine(const VirtualMachine&) = delete;
    VirtualMachine(VirtualMachine&&) = delete;
    VirtualMachine& operator=(const VirtualMachine&) = delete;
    VirtualMachine& operator=(VirtualMachine&&) = delete;

    /** Constructor
     *
     */
    VirtualMachine();
    /** Crea un objeto primitivo nil
     *
     */
    Object *createNil();
    /** Crea un objeto primitivo string
     * @param strString cadena del objeto
     */
    Object *createString(std::string &strString);
    /** Crea un objeto primitivo number
     * @param number número del objeto
     */
    Object *createNumber(float number);
    /** Crea un objeto primitivo booleano
     * @param value estado del objeto booleano
     */
    Object *createBoolean(bool value);
    /** Crea un objeto no primitivo vacio
     */
    Object* createEmptyObject();
    /** Busca un objeto por su ID y lo retorna
     * @param id id del objeto buscado
     */
    Object* findObjectById(uint32_t id);

    /** Setea el lobby de la maquina virtual creado por el workspace
     * @param lobby objeto lobby creado por el workspace
     */
    void setLobby(Object* lobby);
};

#endif /* SERVER_VIRTUALMACHINE_H_ */
