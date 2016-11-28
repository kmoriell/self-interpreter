#ifndef MODESELECTOR_H_
#define MODESELECTOR_H_

#include "server_accepter.h"
#include "common_define.h"
#include <fstream>

/** Es la clase selectora para los dos modos del servidor.
 * El modo servidor propiamente dicho y el modo para levantar
 * archivos locales con codigo self.
 *
 */
class ModeSelector {
public:
    /** Constructor del modo server
     * @param port puerto de escucha del servidor para aceptar conexiones.
     */
    ModeSelector(int port);

    /** Constructor del modo archivo
     * @param filename nombre del archivo con el script en código self
     * que se desea ejecutar.
     */
    ModeSelector(std::string filename);

    /** Constructor por copia deshabilitado
     */
    ModeSelector(const ModeSelector&) = delete;

    /** Constructor por movimiento deshabilitado
     */
    ModeSelector(ModeSelector&&) = delete;

    /** Operador de asignacion deshabilitado
     */
    ModeSelector& operator=(const ModeSelector&) = delete;

    /** Operador de asignacion por moviemiento deshabilitado
     */
    ModeSelector& operator=(ModeSelector&&) = delete;

private:
    /** Metodo que interrumpe al aceptador y joinea el hilo que se abrio
     * @param accepter Objeto aceptador de conexiones.
     */
    void exitRoutine(Accepter* accepter);
};

#endif /* MODESELECTOR_H_ */
