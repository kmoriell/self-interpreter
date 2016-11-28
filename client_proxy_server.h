#ifndef CLIENT_PROXYSERVER_H_
#define CLIENT_PROXYSERVER_H_

#include "common_socket.h"
#include "common_proxy.h"
#include "client_morph.h"
#include "client_parser_protocolo_morph.h"
#include "client_parser_protocolo_workspaces.h"
#include "common_define.h"
#include <vector>
#include <string>
#include <mutex>

/** Es la encargada de enviar las peticiones generadas desde la GUI
 * al servidor.
 *
 */
class ProxyServer: public Proxy {
private:
    /// Morph interno de la clase
    Morph &morph;

    /// Lista de nombres de workspaces
    std::vector<std::string> &workspaces;

    /// Mutex pasado por referencia
    std::mutex &m;

    ///Este flag le indica al proxy que debe ejecutar un comando.
    bool flag;

    /// Mensaje de error si es que hay.
    std::string errorMsg;

private:
    /** Envia el mensaje que esta guardado en message al servidor
     *
     */
    virtual void sendCMDMessage();

public:
    /** Constructor
     * @param socket
     * @papram morph
     * @param workspaces lista de nombres de los workspaces
     * @param m mutex
     */
    ProxyServer(Socket &socket, Morph& morph,
            std::vector<std::string> &workspaces, std::mutex &m);

    /** Envia un mensaje para ejecutar codigo self
     * @param command comando a enviar
     * @param strMessage mensaje a enviar
     */
    bool sendCmdMessage(char command, std::string &strMessage);

    /** Metodo que sirve para procesar la respuesta que le envia el servidor.
     *
     */
    void run();

    /** Obtiene el flag que determina que envio el comando y
     * recibio la respuesta por parte del servidor. Indica
     * que ya se concretaron las operaciones y que se puede
     * volver a enviar nuevamente.
     */
    bool getFlag() const;

    /** Indica si hubo o no errores informados por el servidor.
     *
     */
    bool areThereErrors() const;

    /** Obtiene los errores. Si no hubo ninguno devuelve una cadena vacio, si
     * hay devuelve el error.
     *
     */
    std::string getErrors();

    /** Setea el flag que indica si se esta esperando una respuesta del servidor.
     * @param newValue nuevo valor del flag
     */
    void setFlag(const bool newValue);
};

#endif /* CLIENT_PROXYSERVER_H_ */
