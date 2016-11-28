#ifndef SERVER_PROXYCLIENT_H_
#define SERVER_PROXYCLIENT_H_

#include "common_proxy.h"

/** El ProxyClient es el encargado de responder las peticiones del
 * cliente (ProxyServer). Para resolver las peticiones delega las
 * consultas al servidor(Server/Modelo de Negocio).
 * El ProxyClient solo conoce los IDs del Workspace y de los objetos
 * con los que trabaja.
 *
 */
class ProxyClient: public Proxy {
private:
    /// Servidor al que el proxy le hace las consultas
    Server &server;
    /// Workspace en el que se encuentra el cliente
    std::string idWorkspace;
    /// Pila de IDs de objetos vistos por el cliente
    std::stack<uint32_t> seenObj;
    /// Socket asociado al proxyClient
    Socket* sckptr = nullptr;
public:
    /** Constructor.
     * @param socket socket sobre el cual trabajar
     * @param server referencia al modelo de negocio
     */
    ProxyClient(Socket &socket, Server &server);

    /** Constructor por copia eliminado
     *
     */
    ProxyClient(const ProxyClient&) = delete;

    /** Constructor por moviemiento eliminado
     *
     */
    ProxyClient(ProxyClient&&) = delete;

    /** Operador asignacion eliminado
     *
     */
    ProxyClient& operator=(const ProxyClient&) = delete;

    /** Operador asignacion por moviemiento eliminado
     *
     */
    ProxyClient& operator=(ProxyClient&&) = delete;

    /** Destructor.
     *
     */
    ~ProxyClient();

    /** Metodo que sirve para procesar la solicitud que le envia el cliente.
     *
     */
    virtual void run();
private:
     /** Le pide al servidor que ejecute un script de código self con el
     * entorno/contexto de lobby y le retorna al cliente la respuesta.
     * @param cad script a procesar por el servidor.
     */
    void execLobbyCMD(std::string &cad);
    /** Le pide al servidor que ejecute un script de código self con el
    * entorno/contexto del objeto que ve el cliente y le retorna al cliente
    *  la respuesta.
    * @param cad script a procesar por el servidor.
    */
    void execLocalCMD(std::string &cad);
    /** Le pide al servidor la cadena que representa por protocolo a lobby
     *  y le retorna al cliente la respuesta.
    */
    void showLobby();
    /** Le pide al servidor la cadena que representa por protocolo al
    * objeto que esta viendo el cliente para actualizar las novedades
    * y le retorna al cliente la respuesta.
    */
    void execRefresh();
    /** Le pide al servidor que le setee el nombre al objeto que ve el cliente.
    * Retorna al cliente la respuesta con el objeto modificado.
    * @param cad nuevo nombre.
    */
    void setObjName(const std::string &cad);
    /** Le pide al servidor que le setee el bloque de código al objeto que ve
    * el cliente y retorna al cliente la respuesta con el objeto modificado.
    * @param cad nuevo bloque de codigo.
    */
    void setCodeSegment(const std::string &cad);
    /** Le pide al servidor el objeto contenido en el slot del objeto que el
    * cliente está viendo.
    * @param cad nombre del slot en el objeto que ve el cliente.
    */
    void getSlotObj(const std::string &cad);
    /** Le pide al servidor cambiar la mutabilidad del slot del objeto que el
    * cliente está viendo.
    * @param cad nombre del slot en el objeto que ve el cliente.
    */
    void swapMutability(const std::string &cad);
    /** Le pide al servidor el objeto anterior de la pila seenObj
    * y se lo devuelve al cliente.
    */
    void goBack();
    /** Le pide al servidor una lista de workspaces existentes
    * y le devuelve esa lista al cliente.
    */
    void availableWks();
    /** Le indica al servidor que un cliente va a entrar a un workspace
    * por lo que el servidor le debe retornar el lobby de ese workspace
    * para devolverselo al cliente.
    * @param cad nombre del workspace a cargar.
    */
    void loadWks(const std::string &cad);
    /** Le indica al servidor que se debe crear un nuevo workspace
     * y le retorna al cliente el lobby que le devolvi el server.
    * @param cad nombre del nuevo workspace.
    */
    void newWks(const std::string &cad);
    /** Le indica al servidor que se debe eliminar un workspace
     * y le retorna al cliente la nueva lista de workspace disponibles.
    * @param cad nombre del workspacer a eliminar.
    */
    void deleteWks(const std::string &cad);
    /** Le indica al servidor que el cliente se desconecta del workspace
    *  actual.
    */
    void closeWks();

    /** Devuelve el ID del objeto que está mas arriba en la pila de seenObj.
     * Es decir de los objetos vistos por el cliente hasta el momento.
    */
    uint32_t topObj();
};

#endif /* SERVER_PROXYCLIENT_H_ */
