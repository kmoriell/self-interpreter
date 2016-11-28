#ifndef CLIENT_PROXYSERVER_H_
#define CLIENT_PROXYSERVER_H_

#include "common_socket.h"
#include "common_proxy.h"
#include "client_morph.h"
#include "client_parserProtocoloMorph.h"
#include "client_parserProtocoloWorkspaces.h"
#include "common_define.h"
#include <iostream>
#include <vector>
#include <string>
#include <mutex>

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
     * @param hostname std::string con el nombre del host a conectarse
     * @papram port puerto a conectarse
     * @param morph procesa los datos para luego mostrarlos por pantalla
     */
    ProxyServer(Socket &socket, Morph& morph,
            std::vector<std::string> &workspaces, std::mutex &m);

    /** Envia un mensaje para ejecutar codigo self
     * @param comando a enviar
     * @param mensaje a enviar
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

    void setFlag(const bool newValue);

};

#endif /* CLIENT_PROXYSERVER_H_ */
