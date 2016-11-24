#ifndef COMMON_OBJECT_H_
#define COMMON_OBJECT_H_

#include <string>
#include <stdexcept>
#include <map>
#include <tuple>
#include <vector>
#include <stack>

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
  Object* lobby;
  std::map<Object*, bool> createdObjects;

 private:
  /** Devuelve los parent slots que tiene el objeto.
   *
   */
  slot_map getParentSlots() const;

  /** Devuelve los parent slots del objeto pasado como argumento
   * @param pointer objeto sobre el cual devolver los parent slot.
   */
  Object::slot_map getParentSlots(Object* pointer) const;

  /** Este metodo sirve para buscar el objeto de un slot.
   * @param name nombre del slot a buscar
   * @param returnValue puntero a Object devuelto con el
   * puntero al slot.
   * @param function puntero a funcion devuelto si es un metodo
   *  nativo.
   *  \retval Devuelve true si encontro el objeto seteando
   *  el puntero. Si devuelve false, los punteros estan en nullptr.
   */
  bool findObject(std::string name, Object* &returnValue,
                  delegate& function) const;

  /**
   *
   */
  void configureNativeMethods();

  /**
   *
   */
  void collect_internal();

 public:

  Object();
  /// Constructor
  Object(Object* lobby);

  /// Destructor
  ~Object();

  /// Constructor copia
  Object(const Object& __object);

  /** Constructor por movimiento deshabilitado
   *
   */
  Object(Object&& obj) = delete;

  /** Operador de asignacion deshabilitado
   *
   */
  Object& operator=(const Object& _object) = delete;

  /** Devuelve todos los slots que tiene el objeto.
   *
   */
  slot_map getSlots() const;

  /** Devuelve todo los metodos nativos que tiene el objeto
   *
   */
  std::map<std::string, fpointTuple> getNativeMethods() const;

  /** Funcion nativa para agregar un slot.
   * @param args vector con Object* con los objetos
   * a agregar al slot.
   */
  Object* _AddSlots(const std::vector<Object*>& args);

  /** Agrega el slot con los datos pasados como parametros.
   * @param name nombre del slot.
   * @param obj puntero a Object* para guardar en el slot.
   * @param _mutable booleano que indica si es mutable o no.
   * @param isParentSlot booleano que indica si es parent slot o no.
   * @param isArgument booleano que indica si es argumento o no.
   *
   */
  Object* addSlot(std::string name, Object* obj, bool _mutable,
                  bool isParentSlot, bool isArgument);

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

  /** Determina si es un DataObjecto o un MethodObject.
   * @param messageName nombre del slot.
   *
   */
  bool isDataObject(std::string messageName);

  bool isNativeMethod(std::string messageName);

  /** Metodo principal que sirve para recibir mensajes. Devuelve un Object*
   * @param messageName nombre del slot que va a recibir el mensaje.
   * @param args vector con Object* con los argumentos para pasar.
   *
   */
  Object* recvMessage(std::string messageName, std::vector<Object*> args,
                      bool clonar);

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
   * @param methodName nombre del metodo a habilitar.
   *
   */
  void enableNativeMethod(std::string methodName);

  /** Deshabilita el metodo nativo.
   * @param methodName nombre del metodo a habilitar.
   *
   */
  void disableNativeMethod(std::string methodName);

  void addCreatedObject(Object *obj);

  bool isPrimitive = false;
};

#endif /* COMMON_OBJECT_H_ */
