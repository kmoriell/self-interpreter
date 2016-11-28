#ifndef COMMON_PROXY_H_
#define COMMON_PROXY_H_

#include "common_socket.h"
#include "common_thread.h"
#include "common_message.h"
#include "common_define.h"
#include "server_server.h"
#include "server_object.h"
#include <string>
#include <vector>

/** Esta clase es la base para las clases ProxyClient y ProxyServer.
 * Contiene los metodos y atributos comunes a ambos.
 *
 */
class Proxy: public Thread {
public:
    /** Constructor.
     * @param socket socket sobre el cual trabajar
     */
    Proxy(Socket &socket);

    /** Constructor por copia eliminado
     *
     */
    Proxy(const Proxy&) = delete;

    /** Constructor por moviemiento eliminado
     *
     */
    Proxy(Proxy&&) = delete;

    /** Operador asignacion eliminado
     *
     */
    Proxy& operator=(const Proxy&) = delete;

    /** Operador asignacion por moviemiento eliminado
     *
     */
    Proxy& operator=(Proxy&&) = delete;

    /** Indica si la conexion finalizo.
     *
     */
    bool is_finished();

    /** Interrumpe la ejecucion del proxy.
     *
     */
    void interrupt();

protected:
    /// Socket interno
    Socket &serverSocket;

    /// Flag que indica si hay que interrumpir la recepcion de mensajes.
    bool _interrupt;

    /// Flag que indica si finalizo
    bool finished;

    /// Mensaje recibido
    Message message;

    /** Envia un mensaje
     * @message del tipo command_t con el mensaje
     */
    void send(Message &message);

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

    /** Envia un mensaje de OK para el Morph
     * @param msg con el resultado de la operacion.
     */
    void sendOK(std::string msg);

    /** Envia un mensaje de OK para la ventana selectora de Workspaces
     * @param msg con el resultado de la operacion.
     */
    void sendOKWks(std::string msg);
};

#endif /* COMMON_PROXY_H_ */
