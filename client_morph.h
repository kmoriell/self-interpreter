#ifndef CLIENT_MORPH_H_
#define CLIENT_MORPH_H_

#include <string>
#include <tuple>
#include <vector>

 /** Este objeto contiene la información que ve el cliente desde la GUI
  * y representa al objeto que está visualizando.
 */
class Morph {
public:
    /** Slot del objeto Morph.
     * Elementos de slot_t
     * pos	    tipo		variable
     * 0	    std::string	nombreSlot
     * 1	    bool		esMetodoNativo
     * 2	    bool		esMutable
     * 3	    bool		esArgument
     * 4	    bool		esParent
     * 5	    std::string	nombreObjSlot
     * 6	    std::string	previewObjSlot
     * */
    typedef std::tuple<std::string, bool, bool, bool, bool, std::string,
            std::string> slot_morph;

private:
    std::string objName;
    std::string codeSegment;
    std::vector<slot_morph> slots;

public:
    /** Constructor
     */
    Morph();
    /** Constructor por copia deshabilitado
     */
    Morph(const Morph&) = delete;
    /** Constructor por movimiento deshabilitado
     */
    Morph(Morph&&) = delete;
    /** Operador de asignacion deshabilitado
     */
    Morph& operator=(const Morph&) = delete;
    /** Operador de asignacion por moviemiento deshabilitado
     */
    Morph& operator=(Morph&&) = delete;
    /** Limpia el contenido del morph
     */
    void clear();

    //Getters
    /** Retorna el nombre del objeto.
     */
    std::string getObjName() const;
    /** Retorna el bloque de código del objeto.
     */
    std::string getCodeSegment() const;
    /** Retorna la cantidad de slots del objeto.
     */
    int getSlotsSize() const;
    /** Retorna el nombre del slot indicado.
     * @param nSlot número de slot del que se solicita información.
     */
    std::string getSlotName(int nSlot) const;
    /** Retorna si el slot indicado es un método nativo.
     * @param nSlot número de slot del que se solicita información.
     */
    bool isNativeMethodSlot(int nSlot) const;
    /** Retorna si el slot indicado es mutable.
     * @param nSlot número de slot del que se solicita información.
     */
    bool isMutableSlot(int nSlot) const;
    /** Retorna si el slot indicado es de tipo argumento.
     * @param nSlot número de slot del que se solicita información.
     */
    bool isArgumentSlot(int nSlot) const;
    /** Retorna si el slot indicado es de tipo parent.
     * @param nSlot número de slot del que se solicita información.
     */
    bool isParentSlot(int nSlot) const;
    /** Retorna el nombre del objeto contenido en el slot indicado.
     * @param nSlot número de slot del que se solicita información.
     */
    std::string getSlotObjName(int nSlot) const;
    /** Retorna una cadena con la vista previa del objeto contenido
     * en el slot indicado.
     * @param nSlot número de slot del que se solicita información.
     */
    std::string getSlotObjPreview(int nSlot) const;

    //Setters
    /** Setea el nombre del objeto
     * @param cad nuevo nombre del objeto.
     */
    void setObjName(std::string &cad);
    /** Setea el bloque de código del objeto
     * @param cad nuevo bloque de código del objeto.
     */
    void setCodeSegment(std::string &cad);
    /** Agrega un slot al Objeto Morph
     * @param slotName nombre del slot.
     * @param isNativeMethod indica si es un método nativo.
     * @param isMutable indica si el slot es mutable.
     * @param isArgument indica si el slot es de tipo argumento.
     * @param isParent indica si el slot es de tipo parent.
     * @param objSlotName nombre del objeto contenido en el slot.
     * @param objSlotPreview vista previa del objeto contenido en el slot.
     */
    void addSlot(std::string &slotName, bool isNativeMethod, bool isMutable,
            bool isArgument, bool isParent, std::string &objSlotName,
            std::string &objSlotPreview);
    /** Imprime por pantalla los campos del Morph
     */
    void mostrar();
};

#endif /* CLIENT_MORPH_H_ */
