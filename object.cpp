#include "object.h"

#include <map>
#include <iostream>

Object::Object() {
	this->name = "object";
	this->nativeMethods.insert(std::make_pair("printObj", std::make_tuple(&Object::printObj, true)));
	this->nativeMethods.insert(std::make_pair("print", std::make_tuple(&Object::print, false)));
	this->nativeMethods.insert(std::make_pair("+", std::make_tuple(&Object::operator+, false)));
	this->nativeMethods.insert(std::make_pair("-", std::make_tuple(&Object::operator-, false)));
	this->nativeMethods.insert(std::make_pair("*", std::make_tuple(&Object::operator*, false)));
	this->nativeMethods.insert(std::make_pair("/", std::make_tuple(&Object::operator/, false)));
}

Object::Object(const Object& _lobby) {
	/*  this->slots = _lobby.slots;
	 this->methods = _lobby.methods;
	 this->_mutable = _lobby._mutable;
	 this->name = "copy of " + _lobby.name;*/
}

Object::~Object() {
	slots.clear();
}

void Object::setName(const std::string newName) {
	this->name = newName;
}

std::string Object::getName() const {
	return this->name;
}

void Object::_AddSlots(std::string name, Object* obj, bool _mutable,
		bool isParentSlot) {
	this->slots.insert(
			std::make_pair(name,
					std::make_tuple(obj, _mutable, isParentSlot)));
}

void Object::_RemoveSlots(std::string name) {
	auto it = slots.find(name);
	if (it != slots.end()) {
		slots.erase(it);
	} else
		throw std::runtime_error("No existe el slot que se quiere borrar.");
}

Object* Object::clone(const std::vector<Object *> &args) {
	return new Object(*this);
}

std::string Object::getCodeSegment() const {
	return this->codeSegment;
}

void Object::setCodeSegment(const std::string code) {
	this->codeSegment = code;
}

Object* Object::findObject(std::string name, Object* object) {
	if (name == object->name)
		return object;

	slot_map slots = object->slots;
	auto it = slots.find(name);
	if (it == slots.end()) {
		// Entonces busco en los slots del parent slot
		slot_map parentSlots = getParentSlots();
		std::vector<Object*> parentsFound;

		for (auto _it = parentSlots.begin(); _it != parentSlots.end(); ++_it) {
			Object *_temp = (Object*) std::get < 0 > (_it->second);
			Object *parent = findObject(name, _temp);
			parentsFound.push_back(parent);
		}

		// Tiene que tener unicamente 1 parent slot, si no falla (algo de lookup)
        if (parentsFound.size() != 1) {
            return nullptr;
		}
		return parentsFound[0];
	} else {
		return (Object*)std::get < 0 > (it->second);
	}
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

Object* Object::recvMessage(Object* object, std::string messageName,
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
	Object* message;
	if (!(message = findObject(messageName, object))) {
	    // es un puntero a funcion
	    auto fpoint = object->nativeMethods.find(messageName);
	    if (fpoint == object->nativeMethods.end()) {
	        std::string error = "No existe el mensaje ";
	        error += messageName;
	        throw std::runtime_error(error);
	    }
	    fpointTuple tuple = fpoint->second;
	    if (std::get<1>(tuple)) {
	        // llamo a la funcion apuntada
	        delegate fpointer = std::get<0>(tuple);
	        return (object->*fpointer)(args);
	    } else {
	    	std::string error = "No existe el mensaje ";
	        error += messageName;
	        throw std::runtime_error(error);
	    }
	}
	//slot_t message = findSlot(messageName, object->slots);

	// Una vez que tengo el objeto, necesito los argumentos, si es que tiene
	// y les cambio el valor con los argumentos que se pasaron como parametro
	slot_map object_slots = message->slots;
	uint32_t i = 0;
	for (auto object_slots_it = object_slots.begin();
			object_slots_it != object_slots.end(); ++object_slots_it) {
		// Verifico que la cant de argumentos sean iguales que los pasados,
		// para ahorrar ciclos.
		if (i == args.size())
			break;

		// Verifico que sea argumento y que el slot sea mutable para poder modificarlo
		bool __isMutable = std::get < 1 > (object_slots_it->second);
		std::string slotName = object_slots_it->first;
		if (slotName[0] == ':' && __isMutable) {
			slot_t tupla = object_slots_it->second;

			Object *__object = ((Object*) std::get < 0 > (tupla));
			delete __object;
			__object = args[i];
			std::get < 0 > (tupla) = __object;

			// actualizo el valor del mapa
			object_slots_it->second = tupla;
			i++;
		}
	}

	return message;
}

Object::slot_map Object::getParentSlots() const {
	slot_map parentSlots;
	for (auto it = slots.begin(); it != slots.end(); ++it) {
		if (std::get < 2 > (it->second))
			parentSlots.insert(std::make_pair(it->first, it->second));
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

Object* Object::printObj(const std::vector<Object*>&) {
	std::cout << this << ": ";
	std::cout << "(|";

	for (auto _it = slots.begin(); _it != slots.end(); ++_it) {
		std::string slotName = _it->first;
		std::cout << slotName << std::endl;
		slot_t slot = _it->second;
		std::cout << " " << slotName;

		bool esMutable = std::get < 1 > (slot);
		bool esParent = std::get < 2 > (slot);
		//std::cout << "# Slot: " << nSlot << std::endl;
		if (esMutable)
			std::cout << " <- ";
		else
			std::cout << " = ";
		//std::cout << "Es parent? " << esParent << std::endl;
		std::cout << ".";
	}

	for (auto _it = nativeMethods.begin(); _it != nativeMethods.end(); ++_it) {
		std::string slotNameNative = _it->first;
		fpointTuple tuple = _it->second;
		if (std::get < 1 > (tuple))
			std::cout << " <" << slotNameNative << ">.";
	}

	std::cout << " | ";
	std::cout << codeSegment << " )" << std::endl;
	//std::cout << std::endl;

	for (auto _it = slots.begin(); _it != slots.end(); ++_it) {
		std::string slotName = _it->first;
		slot_t slot = _it->second;
		Object* dirObj;
		dirObj = (Object*) std::get < 0 > (slot);
		if (dirObj != nullptr)
			dirObj->printObj(std::vector<Object*>{});
		else
			std::cout << "ERROR: El Slot no apunta a ningun objeto." << std::endl;
	}
	return this;
}

Object* Object::print(const std::vector<Object*>&) {
	//std::cout << codeSegment.substr(1, codeSegment.size() - 2) << std::endl;
	std::cout << codeSegment << std::endl;
	return this;
}

Object* Object::operator*(const std::vector<Object*>& args) {
    Object* first = (Object*)args[0];
    float number = ::atof(this->codeSegment.c_str());
    float operand = ::atof(first->codeSegment.c_str());
    this->codeSegment = std::to_string(number * operand);
    return this;
}

Object* Object::operator+(const std::vector<Object*>& args) {
    Object* first = (Object*)args[0];
    float number = ::atof(this->codeSegment.c_str());
    float operand = ::atof(first->codeSegment.c_str());
    this->codeSegment = std::to_string(number + operand);
    return this;
}

Object* Object::operator-(const std::vector<Object*>& args) {
    Object* first = (Object*)args[0];
    float number = ::atof(this->codeSegment.c_str());
    float operand = ::atof(first->codeSegment.c_str());
    this->codeSegment = std::to_string(number - operand);
    return this;
}

Object* Object::operator/(const std::vector<Object*>& args) {
    Object* first = (Object*)args[0];
    float number = ::atof(this->codeSegment.c_str());
    float operand = ::atof(first->codeSegment.c_str());
    this->codeSegment = std::to_string(number / operand);
    return this;
}
