#include "server_object.h"

#include <map>
#include <tuple>
#include <iostream>
#include "common_define.h"

Object::Object(Object* lobby) {

  this->lobby = lobby;
  configureNativeMethods();
}

Object::Object() {
  this->lobby = this;
  configureNativeMethods();
}

Object::Object(const Object& __object) {
  this->lobby = __object.lobby;
  // Recorro los slots de __object
  for (auto it = __object.slots.begin(); it != __object.slots.end(); ++it) {
    std::string name = it->first;
    slot_t tuple = it->second;
    Object* obj;

    bool isParentSlot = std::get<2>(tuple);
    if (isParentSlot) {
      obj = (Object*) std::get<0>(tuple);
    } else {
      Object tmpObj = *(Object*) std::get<0>(tuple);
      obj = new Object(tmpObj);

      /*Object *lobby = nullptr;
      delegate fpointer = nullptr;
      __object.findObject("lobby", lobby, fpointer);*/

      lobby->addClonedObj(obj);
    }
    std::get<0>(tuple) = obj;

    this->slots.insert(std::make_pair(name, tuple));
  }

  this->nativeMethods = __object.nativeMethods;
  this->codeSegment = __object.codeSegment;
  this->isPrimitive = __object.isPrimitive;
}

Object::~Object() {
	slots.clear();
	nativeMethods.clear();
	collect(std::vector<Object*>{});
}

void Object::configureNativeMethods() {
  this->nativeMethods.insert(
      std::make_pair(PRINTOBJ_METHOD,
          std::make_tuple(&Object::printObj, true)));
  this->nativeMethods.insert(
      std::make_pair(PRINT_METHOD,
          std::make_tuple(&Object::print, false)));
  this->nativeMethods.insert(
      std::make_pair(OP_SUMA,
          std::make_tuple(&Object::operator+, false)));
  this->nativeMethods.insert(
      std::make_pair(OP_RESTA,
          std::make_tuple(&Object::operator-, false)));
  this->nativeMethods.insert(
      std::make_pair(OP_MULTIPLICACION,
          std::make_tuple(&Object::operator*, false)));
  this->nativeMethods.insert(
      std::make_pair(OP_DIVISION,
          std::make_tuple(&Object::operator/, false)));
  this->nativeMethods.insert(
      std::make_pair(ADD_SLOTS_METHOD,
          std::make_tuple(&Object::_AddSlots, true)));
  this->nativeMethods.insert(
      std::make_pair(REMOVE_SLOTS_METHOD,
          std::make_tuple(&Object::_RemoveSlots, true)));
  this->nativeMethods.insert(
      std::make_pair(CLONE_METHOD,
          std::make_tuple(&Object::clone, true)));
  this->nativeMethods.insert(
      std::make_pair(COLLECT_METHOD,
          std::make_tuple(&Object::collect, false)));
}

Object::slot_map Object::getSlots() const {
	return slots;
}

std::map<std::string, Object::fpointTuple> Object::getNativeMethods() const {
	return nativeMethods;
}

//todo hay que hacer que el addSlots reciba un unico objeto
//y transpase los slots (y sus punteros) del objeto recibido por parametro al objeto propio
Object* Object::_AddSlots(const std::vector<Object*>& args) {
	//Recorro obj y agrego sus slots
	Object *obj = args[0];

	for (auto it = obj->slots.begin(); it != obj->slots.end(); ++it) {
		this->slots.insert(std::make_pair(it->first, it->second));
	}
	return this;
}

Object* Object::addSlot(std::string name, Object* obj, bool _mutable,
		bool isParentSlot, bool isArgument) {
	this->slots.insert(
			std::make_pair(name,
					std::make_tuple(obj, _mutable, isParentSlot, isArgument)));
	return this;
}

Object* Object::_RemoveSlots(const std::vector<Object*>& args) {
	Object *obj = args[0];

	for (auto it = obj->slots.begin(); it != obj->slots.end(); ++it) {
		std::string name = it->first;
		auto _it = slots.find(name);
		if (_it != slots.end()) {
			slots.erase(_it);
		} else
			throw std::runtime_error("No existe el slot que se quiere borrar.");
	}

	return this;
}

Object* Object::removeSlot(std::string name) {
	auto _it = slots.find(name);
	if (_it != slots.end()) {
		slots.erase(_it);
	} else
		throw std::runtime_error("No existe el slot que se quiere borrar.");
	return this;
}

Object* Object::clone(const std::vector<Object *> &args) {
	Object* obj = new Object(*this);
	lobby->addClonedObj(obj);
	return obj;
}

std::string Object::getCodeSegment() const {
	return this->codeSegment;
}

void Object::setCodeSegment(const std::string code) {
	this->codeSegment = code;
}

std::string Object::getName() const {
	return this->name;
}

void Object::setName(const std::string name) {
	this->name = name;
}

bool Object::findObject(std::string name, Object* &returnValue,
		delegate& function) const {

	returnValue = nullptr;
	function = nullptr;

	// Primero me fijo en mis slots
	auto it = slots.find(name);
	if (it != slots.end()) {
		// Significa que lo encontre
		returnValue = (Object*) std::get<0>(it->second);
		return true;
	}

	slot_map parents = getParentSlots();
	for (auto parentSlot_it = parents.begin(); parentSlot_it != parents.end();
			++parentSlot_it) {
		Object* pslot = (Object*) std::get<0>(parentSlot_it->second);
		if (pslot->findObject(name, returnValue, function))
			return true;
	}

	// No lo encontro en sus slots. Busco en los metodos nativos
	auto it_native = nativeMethods.find(name);
	if (it_native != nativeMethods.end()) {
		// Significa que lo encontre
		fpointTuple tuple = it_native->second;

		// Pregunto si esta habilitado
		if (std::get<1>(tuple)) {
			// llamo a la funcion apuntada
			function = std::get<0>(tuple);
			return true;
		}
	}

	// No encontre el metodo nativo
	// Entonces le pregunto a mis parents slots por el slot
	// buscado.


	return false;
}

bool Object::isDataObject(std::string messageName) {

	// Primero verifico que el slot este en la lista de los slots,
	// esto es que este agregado o que se haya sobrecargado un metodo
	// nativo.
	Object* obj; // = nullptr;
	delegate func; // = nullptr;
	bool retval = findObject(messageName, obj, func);

	if (retval && obj) {
	    if (obj->isPrimitive)
	        return true;

		return (obj->codeSegment.size() == 0);
	} else if (retval && func) {
		return false;
	} else {
		std::string error = "El slot " + messageName +
				" no fue encontrado.";
				throw std::runtime_error(error);
	}
}

bool Object::isNativeMethod(std::string messageName) {
	Object* obj;
	delegate func;
	bool retval = findObject(messageName, obj, func);

	return (retval && func);
}

Object* Object::recvMessage(std::string messageName,
		std::vector<Object*> args, bool clonar) {

// Aca tengo mi puntero a objeto, lo que tendria que hacer es ejecutar el codigo
// del mensaje
//Object* foundObject = std::get < 0 > (it->second);
	Object* message; // = nullptr;
	delegate fpointer; // = nullptr;

	if (!findObject(messageName, message, fpointer)) {
		std::string error = messageName + " no encontrado.";
		throw std::runtime_error(error);
	}

// es un puntero a funcion
	if (fpointer != nullptr) {
		if (clonar)
			message = this->clone(std::vector<Object*>{});
		else
			message = this;
		return (message->*fpointer)(args);
	}


// Una vez que tengo el objeto, necesito los argumentos, si es que tiene
// y les cambio el valor con los argumentos que se pasaron como parametro
	if (clonar)
		message = message->clone(std::vector<Object*>{});

	slot_map object_slots = message->slots;
	uint32_t argsCount = 0;
	for (auto object_slots_it = object_slots.begin();
			object_slots_it != object_slots.end(); ++object_slots_it) {
		// Verifico que la cant de argumentos sean iguales que los pasados,
		// para ahorrar ciclos.
		if (argsCount == args.size())
			break;

		// Verifico que sea argumento y que el slot sea mutable para poder modificarlo
		bool __isMutable = std::get<1>(object_slots_it->second);
		bool __isArg = std::get<3>(object_slots_it->second);

		if (__isArg && __isMutable) {
			slot_t tupla = object_slots_it->second;

			Object *__object = ((Object*) std::get<0>(tupla));
			__object = args[argsCount];
			std::get<0>(tupla) = __object;

			// actualizo el valor del mapa
			object_slots_it->second = tupla;
			argsCount++;
		}
	}

	if (argsCount != 0) {
		message->slots = object_slots;
		return message;
	}

	auto it = slots.find(messageName);
	if (it != slots.end() && args.size() > 0) {
		slot_t tuple = it->second;

		if (std::get<1>(tuple)) {
			std::get<0>(tuple) = args[0];
			it->second = tuple;

			return args[0];
		} else {
			std::string error = "El slot no es mutable";
			throw std::runtime_error(error);
		}
	}

	return message;
}

Object::slot_map Object::getParentSlots() const {
	slot_map parentSlots;
	for (auto it = slots.begin(); it != slots.end(); ++it) {
		if (std::get<2>(it->second)) {
			if (std::get<0>(it->second) != this)
				parentSlots.insert(std::make_pair(it->first, it->second));
		}
	}
	return parentSlots;
}

void Object::enableNativeMethod(std::string methodName) {
	auto fpoint = nativeMethods.find(methodName);
	if (fpoint == nativeMethods.end()) {
		std::string error = "No existe el mensaje ";
		error += methodName;
		throw std::runtime_error(error);
	}
	fpointTuple tuple = fpoint->second;
	std::get<1>(tuple) = true;
	fpoint->second = tuple;
}
void Object::disableNativeMethod(std::string methodName) {
	auto fpoint = nativeMethods.find(methodName);
	if (fpoint == nativeMethods.end()) {
		std::string error = "No existe el mensaje ";
		error += methodName;
		throw std::runtime_error(error);
	}
	fpointTuple tuple = fpoint->second;
	std::get<1>(tuple) = false;
	fpoint->second = tuple;
}

void Object::addClonedObj(Object *obj) {
    clonedObjects.push(obj);
}

// Funciones nativas
Object* Object::collect(const std::vector<Object*>& args) {
	while (clonedObjects.size() > 0) {
		Object *obj = clonedObjects.top();
		delete obj;

		clonedObjects.pop();
	}
	return this;
}

Object* Object::printObj(const std::vector<Object*>& args) {
	std::cout << this << " " << name << ": ";
	std::cout << P_LEFT << SLOT_LIST_SEP;

//Escribe los slots (metodos no nativos)
	for (auto _it = slots.begin(); _it != slots.end(); ++_it) {
		std::string slotName = _it->first;
		slot_t slot = _it->second;

		bool esMutable = std::get<1>(slot);
		bool esParent = std::get<2>(slot);
		bool esArgument = std::get<3>(slot);

		std::cout << " ";

		if (esArgument)
			std::cout << OP_ARG;

		std::cout << slotName;

		if (esParent)
			std::cout << OP_PARENT;

		if (esMutable)
			std::cout << " " << OP_SLOT_MUTABLE << " ";
		else
			std::cout << " " << OP_SLOT_INMUTABLE << " ";
		Object* dirObj = (Object*) std::get<0>(slot);
		std::cout << dirObj;
		//std::cout << "Es parent? " << esParent << std::endl;
		std::cout << PUNTO;
	}

//Escribe los slots nativos (metodos nativos)
	for (auto _it = nativeMethods.begin(); _it != nativeMethods.end(); ++_it) {
		std::string slotNameNative = _it->first;
		fpointTuple tuple = _it->second;
		if (std::get<1>(tuple))
			std::cout << " <" << slotNameNative << ">" << PUNTO;
	}

	std::cout << " " << SLOT_LIST_SEP << " ";
	std::cout << codeSegment << " " << P_RIGHT << std::endl;

	for (auto _it = slots.begin(); _it != slots.end(); ++_it) {
		std::string slotName = _it->first;
		slot_t slot = _it->second;
		Object* dirObj;
		dirObj = (Object*) std::get<0>(slot);
		// Es distinto de this para el caso de lobby
		bool esParent = std::get<2>(slot);
		if (dirObj != nullptr && dirObj != this && !esParent)
			dirObj->printObj(std::vector<Object*> { });
		else if (dirObj == nullptr)
			std::cout << "ERROR: El Slot no apunta a ningun objeto."
					<< std::endl;
	}
	return this;
}

Object* Object::print(const std::vector<Object*>& args) {
	std::string _codeSegment = codeSegment.substr(0, codeSegment.size() - 1);

	for (uint32_t i = 0; i <  _codeSegment.size(); i++) {
		size_t pos = _codeSegment.find('\'', i);
		if (pos != std::string::npos)
			_codeSegment.replace(pos, 1, "");
		else
			break;
	}

	if (_codeSegment == "\\n") {
		std::cout << std::endl;
	} else {
		std::cout << _codeSegment;
	}

	return this;
}

//TODO: el casteo (int) es provisorio hasta que el parser
//sepa leer floats, por ahora solo lee naturales
//TODO: al number hay que sacarle el . antes de considerarlo un numero.
//TODO: refactor para no repetir tanto codigo
Object* Object::operator*(const std::vector<Object*>& args) {
	Object *first = (Object*) args[0];

	float number = ::atof(this->codeSegment.c_str());
	float operand = ::atof(first->codeSegment.c_str());
	codeSegment = std::to_string((int) (number * operand)) + PUNTO;
	return this;
}

Object* Object::operator+(const std::vector<Object*>& args) {
	Object *first = (Object*) args[0];

	float number = ::atof(this->codeSegment.c_str());
	float operand = ::atof(first->codeSegment.c_str());
	codeSegment = std::to_string((int) (number + operand)) + PUNTO;
	return this;
}

Object* Object::operator-(const std::vector<Object*>& args) {
	Object *first = (Object*) args[0];

	float number = ::atof(this->codeSegment.c_str());
	float operand = ::atof(first->codeSegment.c_str());
	codeSegment = std::to_string((int) (number - operand)) + PUNTO;
	return this;
}

Object* Object::operator/(const std::vector<Object*>& args) {
	Object *first = (Object*) args[0];

	float number = ::atof(this->codeSegment.c_str());
	float operand = ::atof(first->codeSegment.c_str());
	codeSegment = std::to_string((int) (number / operand)) + PUNTO;
	return this;
}
