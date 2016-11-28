#ifndef SERVER_SERVER_H_
#define SERVER_SERVER_H_

#include <map>
#include <tuple>
#include <stack>
#include <mutex>
#include <string>
#include <stdexcept>
#include <fstream>
#include <vector>
#include "server_object.h"
#include "common_thread.h"
#include "server_workspace.h"
#include "common_define.h"
#include "server_parserProtocoloServidor.h"

/** Representa el modelo de negocio. Resuelve las peticiones de los
 * ProxyClient's y administra los recursos que se deben proteger.
 *
 */
class Server {
private:
    std::mutex m;
    typedef std::tuple<Workspace*, uint32_t> workspace_tuple;
    /** Mapa con clave ID workspaces y valor una tupla con
     * un puntero al workspace y la cantidad de clientes activos en el mismo.
     *
     */
    std::map<std::string, workspace_tuple> workspaces;

private:
    /** Retorna el workspaces en función del id solicitado
     * @param idWk id del workspaces
     */
    Workspace* getWorkspace(const std::string &idWk);

public:
    /** Constructor
     */
    Server();
    /** DEstructor
     */
    ~Server();

    Server(const Server&) = delete;
    Server(Server&&) = delete;
    Server& operator=(const Server&) = delete;
    Server& operator=(Server&&) = delete;

    /** Acumula en el contador de clientes del workspace en el mapa workspaces
    * @param name id del workspace al que se conecta el cliente
     */
    void loadWorkspace(std::string name);
    /** Retorna una cadena por formato de protocolo con la lista de
     * workspaces dispponibles.
     */
    std::vector<std::string> availableWorkspace();
    /** Inicializa un nuevo workspace con el nombre pasado por parametro.
    * @param name id del nuevo workspace
     */
    void newWorkspace(std::string name);
    /** Desacumula en el contador de clientes del workspace en el mapa workspaces
    * @param name id del workspace del que se desconecta el cliente
     */
    void closeWorkspace(std::string name);
    /** Elimina el workspace con el nombre pasado por parametro.
    * @param name id del workspace a eliminar
     */
    void deleteWorkspace(std::string name);
    /** Le pide al workspace que ejecute codigo self con el contexto dado.
    * @param idWk id del workspace
    * @param idObj id del objeto de ese workspace
    * @param code script de código self
     */
    std::string receiveCode(const std::string &idWk, uint32_t &idObj,
            std::string &code);
    /** Le pide el lobby al workspace y genera la cadena del objeto por protocolo
    * @param idWk id del workspace
    * @param idObj id del objeto de ese workspace
     */
    std::string getLobby(const std::string &idWk, uint32_t &idObj);
    /** Le pide el objeto al workspace y genera la cadena del objeto por protocolo
    * @param idWk id del workspace
    * @param idObj id del objeto de ese workspace
     */
    std::string getObj(const std::string &idWk, uint32_t &idObj);
    /** Setea el nombre del objeto y genera la cadena del objeto por protocolo
    * @param idWk id del workspace
    * @param idObj id del objeto de ese workspace
    * @param cad nuevo nombre del objeto
     */
    std::string setObjName(const std::string &idWk, uint32_t &idObj,
            const std::string &cad);
    /** Setea el bloque de código del objeto y genera la cadena del objeto por
     *  protocolo
    * @param idWk id del workspace
    * @param idObj id del objeto de ese workspace
    * @param cad nuevo bloque de código
     */
    std::string setCodeSegment(const std::string &idWk, uint32_t &idObj,
            const std::string &cad);
    /** Genera la cadena por protocolo del objeto contenido en el slot
    * @param idWk id del workspace
    * @param idObj id del objeto de ese workspace
    * @param cad nombre del slot
     */
    std::string getSlotObj(const std::string &idWk, uint32_t &idObj,
            const std::string &cad);
    /** Cambia la mutabilidad del slot y genera la cadena por protocolo del objeto
    * @param idWk id del workspace
    * @param idObj id del objeto de ese workspace
    * @param cad nombre del slot
     */
    std::string swapMutability(const std::string &idWk, uint32_t &idObj,
            const std::string &cad);
};

#endif /* SERVER_SERVER_H_ */
