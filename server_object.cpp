#include "server_object.h"

#include <map>
#include <iostream>

Object::Object() {
	this->nativeMethods.insert(
			std::make_pair("printObj",
					std::make_tuple(&Object::printObj, true)));
	this->nativeMethods.insert(
			std::make_pair("print", std::make_tuple(&Object::print, false)));
	this->nativeMethods.insert(
			std::make_pair("+", std::make_tuple(&Object::operator+, false)));
	this->nativeMethods.insert(
			std::make_pair("-", std::make_tuple(&Object::operator-, false)));
	this->nativeMethods.insert(
			std::make_pair("*", std::make_tuple(&Object::operator*, false)));
	this->nativeMethods.insert(
			std::make_pair("/", std::make_tuple(&Object::operator/, false)));
	this->nativeMethods.insert(
			std::make_pair("_AddSlots",
					std::make_tuple(&Object::_AddSlots, true)));
	this->nativeMethods.insert(
			std::make_pair("_RemoveSlots",
					std::make_tuple(&Object::_RemoveSlots, true)));
	this->nativeMethods.insert(
			std::make_pair("clone", std::make_tuple(&Object::clone, true)));
}

Object::Object(const Object& __object) {
	// Recorro los slots de __object
	for (auto it = __object.slots.begin(); it != __object.slots.end(); ++it) {
		std::string name = it->first;
		slot_t tuple = it->second;
		Object* obj;
		if (name == "self")
			continue;

		if (name == "lobby") { //En realidad si es parent slot.
			obj = std::get<0>(tuple);
		} else {
			Object tmpObj = *(Object*) std::get<0>(tuple);
			obj = new Object(tmpObj);
		}

		std::get<0>(tuple) = obj;

		this->slots.insert(std::make_pair(name, tuple));
	}

	this->nativeMethods = __object.nativeMethods;
	this->codeSegment = __object.codeSegment;
}

Object::~Object() {
	slots.clear();
	nativeMethods.clear();
}

Object::slot_map Object::getSlots() const {
	return slots;
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
	//std::cout << "Clonacion... 1" << std::endl;
	return new Object(*this);
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

/*
 void Object::findObject(std::string name, Object* scope, Object* &returnValue,
 delegate& function) {
 if (name == "")
 return;

 function = nullptr;
 slot_map slots = scope->slots;
 auto it = slots.find(name);
 if (it == slots.end()) {
 //Busco en los metodos nativos
 auto fpoint = scope->nativeMethods.find(name);
 bool nativeMethodFound = true;
 if (fpoint == scope->nativeMethods.end()) {
 nativeMethodFound = false;
 } else {
 fpointTuple tuple = fpoint->second;
 if (std::get<1>(tuple)) {
 // llamo a la funcion apuntada
 function = std::get<0>(tuple);
 return;
 }
 }
 // Entonces busco en los slots del parent slot
 slot_map parentSlots = getParentSlots(this);
 //std::vector<Object*> parentsFound;

 auto _slot = parentSlots.find(name);

 if (_slot != parentSlots.end())
 returnValue = (Object*) std::get<0>(_slot->second);
 else {
 for (auto _it = parentSlots.begin(); _it != parentSlots.end(); ++_it) {
 Object* __parent = (Object*) std::get<0>(_slot->second);
 __parent->findObject(name,__parent, returnValue, function);
 }
 std::string error = "No existe el mensaje ";
 error += name;
 throw std::runtime_error(error);
 }

 for (auto _it = parentSlots.begin(); _it != parentSlots.end(); ++_it) {
 Object *_temp = (Object*) std::get<0>(_it->second);
 Object *parent = nullptr;
 findObject(name, _temp, parent, function);
 if (parent != nullptr)
 parentsFound.push_back(parent);
 }

 // Tiene que tener unicamente 1 parent slot, si no falla (algo de lookup)
 if (parentsFound.size() != 1 && !nativeMethodFound) {

 }
 returnValue = parentsFound[0];
 } else {
 returnValue = (Object*) std::get<0>(it->second);
 }
 }*/

bool Object::findObject(std::string name, Object* &returnValue,
		delegate& function) {

	// Primero me fijo en mis slots
	auto it = slots.find(name);
	if (it != slots.end()) {
		// Significa que lo encontre
		returnValue = (Object*) std::get<0>(it->second);
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
	slot_map parents = getParentSlots();
	for (auto parentSlot_it = parents.begin(); parentSlot_it != parents.end();
			++parentSlot_it) {
		Object* pslot = (Object*) std::get<0>(parentSlot_it->second);
		if (pslot->findObject(name, returnValue, function))
			return true;
	}

	return false;
}

/*slot_t Object::findSlot(std::string name, slot_map slots) {
 auto it = slots.find(name);
 if (it == slots.end()) {
 // Entonces busco en los slots del parent slot
 slot_map parentSlots = getParentSlots();
 std::vector<slot_t> parentsFound;

 for (auto _it = parentSlots.begin(); _it != parentSlots.end(); ++_it) {
 slot_t parent = findSlot(name, _it->second);
 parentsFound.push_back(parent);
 }

 // Tiene que tener unicamente 1 parent slot, si no falla (algo de lookup)
 if (parentsFound.size() != 1) {
 std::string error = "Slot ";
 error += this->name + " no encontrado.";
 throw std::runtime_error(error);
 }
 return parentsFound[0];
 } else {
 return it->second;
 }
 }*/

/*Object* Object::recvMessage(std::string objectName, std::string messageName,
 std::vector<opcode_t> args) {
 Object* object = findObject(objectName, this);

 if (messageName == "")
 return object;

 return recvMessage(object, messageName, args);
 }*/

Object* Object::recvMessage(std::string messageName,
		std::vector<Object*> args) {
	/*// Reviso en los slots del objeto si existe el mensaje
	 auto it = object->slots.find(message);
	 if (it == object->slots.end()) {
	 // Entonces busco en los slots del parent slot
	 auto parentSlots = getParentSlots();
	 std::vector<Object*> parentsFound;

	 for (auto _it = parentSlots.begin(); _it != parentSlots.end(); ++_it) {
	 Object *parent = std::get < 0 > (_it->second);
	 parentsFound.push_back(parent);
	 }

	 // Tiene que tener unicamente 1 parent slot, si no falla (algo de lookup)
	 if (parentsFound.size() != 1) {
	 std::string error = message;
	 error += " no reconocido por " + this->name;
	 throw std::runtime_error(error);
	 }
	 return recvMessage(parentsFound[0], message, args);

	 } else {*/

	// Aca tengo mi puntero a objeto, lo que tendria que hacer es ejecutar el codigo
	// del mensaje
	//Object* foundObject = std::get < 0 > (it->second);
	Object* message = nullptr;
	delegate fpointer = nullptr;

	if (!findObject(messageName, message, fpointer)) {
		std::string error = messageName + " no encontrado.";
		throw std::runtime_error(error);
	}

	// es un puntero a funcion
	if (fpointer != nullptr)
		return (this->*fpointer)(args);

	//slot_t message = findSlot(messageName, object->slots);

	// Una vez que tengo el objeto, necesito los argumentos, si es que tiene
	// y les cambio el valor con los argumentos que se pasaron como parametro
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
			delete __object;
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

void Object::enableNativeMethod(Object* object, std::string methodName) {
	auto fpoint = object->nativeMethods.find(methodName);
	if (fpoint == object->nativeMethods.end()) {
		std::string error = "No existe el mensaje ";
		error += methodName;
		throw std::runtime_error(error);
	}
	fpointTuple tuple = fpoint->second;
	std::get<1>(tuple) = true;
	fpoint->second = tuple;
}
void Object::disableNativeMethod(Object* object, std::string methodName) {
	auto fpoint = object->nativeMethods.find(methodName);
	if (fpoint == object->nativeMethods.end()) {
		std::string error = "No existe el mensaje ";
		error += methodName;
		throw std::runtime_error(error);
	}
	fpointTuple tuple = fpoint->second;
	std::get<1>(tuple) = false;
	fpoint->second = tuple;
}

// Funciones nativas

Object* Object::printObj(const std::vector<Object*>& args) {
	std::cout << this << ": ";
	std::cout << "(|";

	//Escribe los slots (metodos no nativos)
	for (auto _it = slots.begin(); _it != slots.end(); ++_it) {
		std::string slotName = _it->first;
		slot_t slot = _it->second;

		bool esMutable = std::get<1>(slot);
		bool esParent = std::get<2>(slot);
		bool esArgument = std::get<3>(slot);

		std::cout << " ";

		if (esArgument)
			std::cout << ":";

		std::cout << slotName;

		if (esParent)
			std::cout << "*";

		if (esMutable)
			std::cout << " <- ";
		else
			std::cout << " = ";
		Object* dirObj = (Object*) std::get<0>(slot);
		std::cout << dirObj;
		//std::cout << "Es parent? " << esParent << std::endl;
		std::cout << ".";
	}

	//Escribe los slots nativos (metodos nativos)
	for (auto _it = nativeMethods.begin(); _it != nativeMethods.end(); ++_it) {
		std::string slotNameNative = _it->first;
		fpointTuple tuple = _it->second;
		if (std::get<1>(tuple))
			std::cout << " <" << slotNameNative << ">.";
	}

	std::cout << " | ";
	std::cout << codeSegment << " )" << std::endl;
	//std::cout << std::endl;

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

	for (char c : _codeSegment) {
		size_t pos = _codeSegment.find('\'');
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

Object* Object::operator*(const std::vector<Object*>& args) {
	Object *first = (Object*) args[0];
	Object *result = new Object(*this);

	float number = ::atof(this->codeSegment.c_str());
	float operand = ::atof(first->codeSegment.c_str());
	result->codeSegment = std::to_string(number * operand);
	return result;

	/*Object* first = (Object*) args[0];
	float number = ::atof(this->codeSegment.c_str());
	float operand = ::atof(first->codeSegment.c_str());
	setCodeSegment(std::to_string(number+operand)+PUNTO);
	return this;*/
}

Object* Object::operator+(const std::vector<Object*>& args) {
	Object *first = (Object*) args[0];
	Object *result = new Object(*this);

	float number = ::atof(this->codeSegment.c_str());
	float operand = ::atof(first->codeSegment.c_str());
	result->codeSegment = std::to_string(number + operand);
	return result;

	/*Object* first = (Object*) args[0];
	float number = ::atof(this->codeSegment.c_str());
	float operand = ::atof(first->codeSegment.c_str());
	setCodeSegment(std::to_string(number+operand)+PUNTO);
	return this;*/
}

Object* Object::operator-(const std::vector<Object*>& args) {
	Object* first = (Object*) args[0];
	Object *result = new Object(*this);

	float number = ::atof(this->codeSegment.c_str());
	float operand = ::atof(first->codeSegment.c_str());
	result->codeSegment = std::to_string(number - operand);
	return result;

	/*Object* first = (Object*) args[0];
	float number = ::atof(this->codeSegment.c_str());
	float operand = ::atof(first->codeSegment.c_str());
	setCodeSegment(std::to_string(number-operand)+PUNTO);
	return this;*/
}

Object* Object::operator/(const std::vector<Object*>& args) {
	Object* first = (Object*) args[0];
	Object *result = new Object(*this);

	float number = ::atof(this->codeSegment.c_str());
	float operand = ::atof(first->codeSegment.c_str());
	result->codeSegment = std::to_string(number / operand);
	return result;

	/*Object* first = (Object*) args[0];
	float number = ::atof(this->codeSegment.c_str());
	float operand = ::atof(first->codeSegment.c_str());
	setCodeSegment(std::to_string(number/operand)+PUNTO);
	return this;*/
}
