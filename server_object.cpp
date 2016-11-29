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

            auto tuple = std::make_tuple(obj, false);
            // Creo una tupla con el nuevo objeto creado
            // Despues lo inserto en la lista de objetos creados de lobby.
            lobby->createdObjects.insert(
                    std::make_pair(lobby->idCounter, tuple));
            id = lobby->idCounter;
            lobby->idCounter++;

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

    std::stack<Object*> objects;

    for (auto it = createdObjects.begin(); it != createdObjects.end(); ++it) {
        auto tuple = it->second;
        objects.push(std::get<0>(tuple));
    }
    createdObjects.clear();
    while (objects.size() > 0) {
        Object *obj = objects.top();
        delete obj;

        objects.pop();
    }
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
            std::make_pair(OP_IGUAL,
                    std::make_tuple(&Object::operator==, false)));
    this->nativeMethods.insert(
            std::make_pair(OP_DISTINTO,
                    std::make_tuple(&Object::operator!=, false)));
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

Object* Object::addSlot(std::string name, Object* obj, bool _mutable,
        bool isParentSlot, bool isArgument) {
    this->slots.insert(
            std::make_pair(name,
                    std::make_tuple(obj, _mutable, isParentSlot, isArgument)));
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

uint32_t Object::getId() const {
    return id;
}

void Object::setPrimitive(const bool newValue) {
    isPrimitive = newValue;
}

bool Object::getPrimitive() const {
    return isPrimitive;
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

    return false;
}

bool Object::isDataObject(std::string messageName) {
    // Primero verifico que el slot este en la lista de los slots,
    // esto es que este agregado o que se haya sobrecargado un metodo
    // nativo.
    Object* obj;  // = nullptr;
    delegate func;  // = nullptr;
    bool retval = findObject(messageName, obj, func);

    if (retval && obj) {
        if (obj->isPrimitive)
            return true;

        return (obj->codeSegment.size() == 0);
    } else if (retval && func) {
        return false;
    } else {
        std::string error = "El slot " + messageName + " no fue encontrado.";
        throw std::runtime_error(error);
    }
}

bool Object::isDataObject() {
    if (isPrimitive)
        return true;

    return (codeSegment.size() == 0);
}

bool Object::isNativeMethod(std::string messageName) {
    Object* obj;
    delegate func;
    bool retval = findObject(messageName, obj, func);

    return (retval && func);
}

Object* Object::recvMessage(std::string messageName, std::vector<Object*> args,
        bool clone) {
    Object* message;
    delegate fpointer;

    // Busco el slot solicitado
    if (!findObject(messageName, message, fpointer)) {
        std::string error = messageName + " no encontrado.";
        throw std::runtime_error(error);
    }

    // si fpointer no es nullptr, es un puntero a una funcion nativa
    if (fpointer != nullptr) {
        if (clone)
            message = this->clone(std::vector<Object*> { });
        else
            message = this;

        // Devuelvo el resultado de la llamada a la funcion
        // nativa.
        return (message->*fpointer)(args);
    }

    // Si hay que clonar, clono el mensaje para luego modificarle
    // los argumentos
    if (clone)
        message = message->clone(std::vector<Object*> { });

    // Una vez que tengo el objeto, necesito los argumentos, si es que tiene
    // y les cambio el valor con los argumentos que se pasaron como parametro
    slot_map object_slots = message->slots;

    // Contador de argumentos
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
            slot_t tuple = object_slots_it->second;

            Object *__object = ((Object*) std::get<0>(tuple));
            __object = args[argsCount];
            std::get<0>(tuple) = __object;

            // actualizo el valor del mapa
            object_slots_it->second = tuple;
            argsCount++;
        }
    }

    // Si hay argumentos significa que hay que cambiar
    // los punteros de los argumentos.
    if (argsCount != 0) {
        message->slots = object_slots;
        return message;
    }

    // Busco en los slots el mensaje, lo que se esta implementando aca
    // es un cambio de valor de un objeto mutable.
    // Si no es mutable, genera excepcion.
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

void Object::addCreatedObject(Object *obj) {
    auto tuple = std::make_tuple(obj, false);
    lobby->createdObjects.insert(std::make_pair(lobby->idCounter, tuple));
    obj->id = lobby->idCounter;
    lobby->idCounter++;
}

Object* Object::findObjectById(uint32_t id) {
    if (id == ID_LOBBY)
        return lobby;
    auto it = createdObjects.find(id);

    if (it == createdObjects.end()) {
        std::string error = "No existe un objeto con el id "
                + std::to_string(id);
        throw std::runtime_error(error);
    } else
        return std::get<0>(it->second);
}

void Object::collect_internal() {
    // Recorro todos los slots,
    for (auto object_slots_it = slots.begin(); object_slots_it != slots.end();
            ++object_slots_it) {
        slot_t tuple = object_slots_it->second;

        // Si no es parent slot, llamo recursivamente
        // a collect_internal para ir marcando los objetos
        // que no tienen acceso desde lobby.
        if (!std::get<2>(tuple)) {
            Object* slotObj = std::get<0>(tuple);
            slotObj->collect_internal();

            // busco el objeto (por su direccion de memoria) y
            // lo marco, indicando que se puede acceder desde lobby.
            for (auto it = lobby->createdObjects.begin();
                    it != lobby->createdObjects.begin(); ++it) {
                auto _tuple = it->second;
                if (std::get<0>(_tuple) == slotObj) {
                    std::get<1>(_tuple) = true;
                }
            }
        }
    }
}

void Object::swapSlotMutability(const std::string& slotName) {

    auto it = slots.find(slotName);
    if (it != slots.end()) {
        auto tuple = it->second;

        bool _mutable = std::get<1>(tuple);

        std::get<1>(tuple) = !_mutable;
        it->second = tuple;
    } else {
        throw std::runtime_error("El slot buscado no existe");
    }
}

// Funciones nativas
Object* Object::_AddSlots(const std::vector<Object*>& args) {
    //Recorro obj y agrego sus slots
    Object *obj = args[0];

    for (auto it = obj->slots.begin(); it != obj->slots.end(); ++it) {
        this->slots.insert(std::make_pair(it->first, it->second));
    }
    return this;
}

Object* Object::_RemoveSlots(const std::vector<Object*>& args) {
    Object *obj = args[0];

    for (auto it = obj->slots.begin(); it != obj->slots.end(); ++it) {
        std::string name = it->first;
        auto _it = slots.find(name);
        if (_it != slots.end()) {
            slots.erase(_it);
        } else {
            disableNativeMethod(name);
        }
    }
    return this;
}

Object* Object::clone(const std::vector<Object *> &args) {
    Object* obj = new Object(*this);

    auto tuple = std::make_tuple(obj, false);
    lobby->createdObjects.insert(std::make_pair(lobby->idCounter, tuple));
    id = lobby->idCounter;
    lobby->idCounter++;
    return obj;
}

Object* Object::collect(const std::vector<Object*>& args) {
    collect_internal();

    std::vector<uint32_t> deleteObjects;
    // Recorro los objetos creados, el unico objeto que
    // va a tener es lobby. Reviso que no esten marcados
    // los guardo en un vector para luego hacerles el delete.
    for (auto it = createdObjects.begin(); it != createdObjects.end(); ++it) {
        auto tuple = it->second;
        if (!std::get<1>(tuple)) {
            deleteObjects.push_back(it->first);
        }
    }

    for (auto id : deleteObjects) {
        Object* obj = std::get<0>((createdObjects.find(id))->second);
        createdObjects.erase(id);
        delete obj;
    }

    deleteObjects.clear();

    // Reconfiguro la lista para que vuelva a funcionar el GC
    // en una proxima iteracion.
    for (auto it = createdObjects.begin(); it != createdObjects.end(); ++it) {
        auto _tuple = it->second;
        std::get<1>(_tuple) = true;

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

    for (uint32_t i = 0; i < _codeSegment.size(); i++) {
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

Object* Object::operator*(const std::vector<Object*>& args) {
    Object *first = (Object*) args[0];
    std::string strCodeSegment = this->codeSegment.substr(0,
            codeSegment.size() - 1);
    std::string argCodeSegment = first->codeSegment.substr(0,
            first->codeSegment.size() - 1);

    float number = std::stof(strCodeSegment);
    float operand = std::stof(argCodeSegment);
    codeSegment = std::to_string((int) (number * operand)) + PUNTO;
    return this;
}

Object* Object::operator+(const std::vector<Object*>& args) {
    Object *first = (Object*) args[0];
    std::string strCodeSegment = this->codeSegment.substr(0,
            codeSegment.size() - 1);
    std::string argCodeSegment = first->codeSegment.substr(0,
            first->codeSegment.size() - 1);

    float number = std::stof(strCodeSegment);
    float operand = std::stof(argCodeSegment);
    codeSegment = std::to_string((int) (number + operand)) + PUNTO;
    return this;
}

Object* Object::operator-(const std::vector<Object*>& args) {
    Object *first = (Object*) args[0];
    std::string strCodeSegment = this->codeSegment.substr(0,
            codeSegment.size() - 1);
    std::string argCodeSegment = first->codeSegment.substr(0,
            first->codeSegment.size() - 1);

    float number = std::stof(strCodeSegment);
    float operand = std::stof(argCodeSegment);
    codeSegment = std::to_string((int) (number - operand)) + PUNTO;
    return this;
}

Object* Object::operator/(const std::vector<Object*>& args) {
    Object *first = (Object*) args[0];
    std::string strCodeSegment = this->codeSegment.substr(0,
            codeSegment.size() - 1);
    std::string argCodeSegment = first->codeSegment.substr(0,
            first->codeSegment.size() - 1);

    float number = std::stof(strCodeSegment);
    float operand = std::stof(argCodeSegment);
    codeSegment = std::to_string((int) (number / operand)) + PUNTO;
    return this;
}

Object* Object::operator==(const std::vector<Object*>& args) {
    Object *first = (Object*) args[0];
    std::string strCodeSegment = this->codeSegment.substr(0,
            codeSegment.size() - 1);
    std::string argCodeSegment = first->codeSegment.substr(0,
            first->codeSegment.size() - 1);

    bool retVal = true;

    if (strCodeSegment.front() == '\'' && strCodeSegment.back() == '\''
            && argCodeSegment.front() == '\''
            && argCodeSegment.back() == '\'') {
        retVal = (strCodeSegment == argCodeSegment);
    } else {
        float number = std::stof(strCodeSegment);
        float operand = std::stof(argCodeSegment);
        retVal = (number == operand);
    }

    slots.clear();
    disableNativeMethod(OP_SUMA);
    disableNativeMethod(OP_RESTA);
    disableNativeMethod(OP_MULTIPLICACION);
    disableNativeMethod(OP_DIVISION);
    codeSegment = (retVal ? TRUE_STR : FALSE_STR) + PUNTO;
    return this;
}

Object* Object::operator!=(const std::vector<Object*>& args) {
    Object* obj = this->operator==(args);
    std::string strCodeSegment = obj->codeSegment.substr(0,
            codeSegment.size() - 1);

    if (strCodeSegment == TRUE_STR)
        obj->codeSegment = FALSE_STR;
    else
        obj->codeSegment = TRUE_STR;

    obj->codeSegment += PUNTO;

    return obj;
}
