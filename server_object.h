#ifndef COMMON_OBJECT_H_
#define COMMON_OBJECT_H_

#include <string>
#include <stdexcept>
#include <map>
#include <tuple>
#include <vector>

class Object {
public:
	typedef Object* (Object::*delegate)(const std::vector<Object*>&);

	/* puntero a Object con la referencia al objeto*
	 * booleano que indica si es mutable o no
	 * booleano que indica si el objeto apuntado es un parent slot
	 * booleano que indica si esta implementado nativamente
	 * booleano que indica si es un argumento (:)
	 */
	typedef std::tuple<Object*, bool, bool, bool> slot_t;
	typedef std::map<std::string, slot_t> slot_map;
	typedef std::tuple<delegate, bool> fpointTuple;
private:
	slot_map slots;
	std::string name;
	std::string codeSegment;
	std::map<std::string, fpointTuple> nativeMethods;

	slot_map getParentSlots() const;
	Object::slot_map getParentSlots(Object* pointer) const;
	bool findObject(std::string name, Object* &returnValue,
			delegate& function);

public:
	/// Constructor
	Object();

	/// Destructor
	~Object();

	/// Constructor copia
	Object(const Object& __object);

	/** Devuelve todos los slots que tiene el objeto.
	 *
	 */
	slot_map getSlots() const;

	/** Devuelve todo los metodos nativos que tiene el objeto
	 *
	 */
	std::map<std::string,fpointTuple> getNativeMethods() const;

	/** Funcion nativa para agregar un slot.
	 * @param args vector con Object* con los objetos
	 * a agregar al slot.
	 */
	Object* _AddSlots(const std::vector<Object*>& args);

	/** Agrega el slot con los datos pasados como parametros.
	 * @param name nombre del slot.
	 * @param objm puntero a Object* para guardar en el slot.
	 * @_mutable booleano que indica si es mutable o no.
	 * @isParentSlot booleano que indica si es parent slot o no.
	 * @isArgument booleano que indica si es argumento o no.
	 *
	 */
	Object* addSlot(std::string name, Object* obj, bool _mutable, bool isParentSlot, bool isArgument);

	/** Funcion nativa para borrar un slot.
	 * @param args vector con Object* con los objetos para borrar.
	 */
	Object* _RemoveSlots(const std::vector<Object*>& args);

	/** Borra el slot especificado
	 * @param name indica el nombre del slot a borrar.
	 */
	Object* removeSlot(std::string name);

	/** Agrega como code segment del objeto la cadena que se la pasa
	 * @param code std::string pasado con el codigo para reemplazar en el code segment.
	 */
	void setCodeSegment(const std::string code);

	/** Devuelve el code segment del objeto.
	 *
	 */
	std::string getCodeSegment() const;

	/** Setea el nombre del objeto
	 * @param name std::string con el nombre del objeto para cambiar.
	 */
	void setName(const std::string name);

	/** Devuelve un std::string con el nombre del objeto.
	 *
	 */
	std::string getName() const;

	/** Metodo principal que sirve para recibir mensajes. Devuelve un Object*
	 * @param messageName nombre del slot que va a recibir el mensaje
	 * @param args vector con Object* con los argumentos para pasar.
	 *
	 */
	Object* recvMessage(std::string messageName,
			std::vector<Object*> args);

	/** Metodo nativo para clonar el objeto.
	 * @param args vector de Object* vacio.
	 */
	Object* clone(const std::vector<Object*>& args);

	/** Metodo nativo para invocar el garbage collector.
	 * @param args vector de Object* vacio.
	 */
	Object* collect(const std::vector<Object*>& args);

	// funciones Nativas
	/** Metodo nativo para imprimir por pantalla.
	 * @param args vector de Object* vacio.
	 */
	Object* print(const std::vector<Object*>& args);

	/** Metodo nativo para imprimir por pantalla datos de debugging.
	 * @param args vector de Object* vacio.
	 */
	Object* printObj(const std::vector<Object*>& args);

	/** Metodo nativo para efectuar la multiplicacion
	 * @param args vector de Object* vacio.
	 */
	Object* operator*(const std::vector<Object*>& args);

	/** Metodo nativo para efectuar la suma
	 * @param args vector de Object* vacio.
	 */
	Object* operator+(const std::vector<Object*>& args);

	/** Metodo nativo para efectuar la resta
	 * @param args vector de Object* vacio.
	 */
	Object* operator-(const std::vector<Object*>& args);

	/** Metodo nativo para efectuar la division
	 * @param args vector de Object* vacio.
	 */
	Object* operator/(const std::vector<Object*>& args);

	/** Habilita el metodo nativo.
	 * @param object Object* que va a ser modificado y donde esta el metodo
	 * @param methodName nombre del metodo a habilitar.
	 *
	 */
	void enableNativeMethod(Object* object, std::string methodName);

	/** Deshabilita el metodo nativo.
	 * @param object Object* que va a ser modificado y donde esta el metodo
	 * @param methodName nombre del metodo a habilitar.
	 *
	 */
	void disableNativeMethod(Object* object, std::string methodName);
};

#endif /* COMMON_OBJECT_H_ */
