#include "object.h"

#include <map>
#include <iostream>

Object::Object() {
	this->name = "object";
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
		bool isParentSlot, bool isNative) {
	/*delegate _delegate;

	 if (isNative) {
	 _delegate = &Object::print;
	 void *pointer = _delegate;
	 Object* (*func)(const std::vector<Object*>&) = (Object*(*)(const std::vector<Object*>&))message;
	 }*/

	this->slots.insert(
			std::make_pair(name,
					std::make_tuple(obj, _mutable, isParentSlot, isNative)));
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

bool Object::findObject(std::string name, Object* object, Object* &messsage) {
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
			Object *parent;
			findObject(name, _temp, parent);
			parentsFound.push_back(parent);
		}

		// Tiene que tener unicamente 1 parent slot, si no falla (algo de lookup)
		if (parentsFound.size() != 1) {
			std::string error = "Objeto ";
			error += name + " no encontrado.";
			throw std::runtime_error(error);
		}
		return parentsFound[0];
	} else {
		messsage = std::get < 0 > (it->second);
		return std::get < 3 > (it->second);
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
	if (findObject(messageName, object, message)) {
		//ejecuto message;
		Object* (*func)(
				const std::vector<Object*>&) = (Object*(*)(const std::vector<Object*>&))message;
		//delegate method = reinterpret_cast<delegate>(message);

		return (func)(args);
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

Object* Object::print(const std::vector<Object*>&) {
	std::cout << codeSegment << std::endl;
	return this;
}

void Object::mostrar() {
	std::cout << std::endl;
	std::cout << "Nombre objeto: " << name << std::endl;
	std::cout << "Direccion objeto: " << this << std::endl;
	if (codeSegment == "")
		std::cout << "Code Segment: " << std::endl;
	else
		std::cout << "Code Segment: " << std::endl << codeSegment << std::endl;
	std::cout << "Número de slots: " << slots.size() << std::endl;
	int nSlot = 1;
	for (auto _it = slots.begin(); _it != slots.end(); ++_it) {
		std::string slotName = _it->first;
		slot_t slot = _it->second;
		bool esMutable = std::get < 1 > (slot);
		bool esParent = std::get < 2 > (slot);
		std::cout << "# Slot: " << nSlot << std::endl;
		std::cout << "SlotName " << nSlot << ": " << slotName << std::endl;
		std::cout << "Es mutable? " << esMutable << std::endl;
		std::cout << "Es parent? " << esParent << std::endl;
		Object* dirObj;
		dirObj = (Object*) std::get < 0 > (slot);
		if (dirObj != nullptr)
			dirObj->mostrar();
		else
			std::cout << "El Slot no apunta a ningun objeto." << std::endl;
		nSlot++;
	}
}
