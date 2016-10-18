#include "lobby.h"
#include <map>

Lobby::Lobby() {
    this->name = "object";
    this->methods.insert(std::make_pair("+", &Lobby::operator+));
    this->methods.insert(std::make_pair("*", &Lobby::operator*));
    this->methods.insert(std::make_pair("-", &Lobby::operator-));
    this->methods.insert(std::make_pair("/", &Lobby::operator/));
    this->methods.insert(std::make_pair("<-", &Lobby::mutableAsignation));
    //this->methods.insert(std::make_pair("=", &Lobby::operator=));
    this->methods.insert(std::make_pair("print", &Lobby::print));
}

Lobby::Lobby(const Lobby& _lobby) {
    this->slots = _lobby.slots;
    this->methods = _lobby.methods;
    this->_mutable = _lobby._mutable;
    this->name = "copy of " + _lobby.name;
}

Lobby::~Lobby() {
    slots.clear();
    methods.clear();
}

void Lobby::setName(std::string newName) {
this->name = newName;
}

void Lobby::_AddSlots(std::string name, slot_t newSlot) {
    // Verifico que no haya un metodo con el mismo nombre
    // porque si hay, significa que estoy sobreescribiendo
    auto it = methods.find(name);
    if (it != methods.end()) {
        methods.erase(it);
    }
    this->slots.insert(std::make_pair(name, newSlot));
}

void Lobby::_RemoveSlots (std::string name) {
 auto it = slots.find(name);
    if (it != slots.end()) {
        slots.erase(it);
    } else
        throw std::runtime_error(
        "No existe el slot que se quiere borrar.");
}

void Lobby::setMutable(bool state) {
    this->_mutable = state;
}

bool Lobby::getMutable() const {
    return this->_mutable;
}

Lobby* Lobby::clone(const std::vector<Lobby *> &args) {
    return new Lobby(*this);
}

Lobby::delegate Lobby::getMethod(std::string name) const {
    auto it = methods.find(name);

    if (it != methods.end())
        return it->second;
    else
        return nullptr;
}

slot_t Lobby::getSlot(std::string name) const {
    auto it = this->slots.find(name);
    if (it != slots.end())
        return it->second;
    else {
        std::string error = "No existe el slot buscado. Slot: ";
        error += name;
        throw std::runtime_error(error);
    }
}

Lobby* Lobby::operator=(const std::vector<Lobby*>& args) {
    throw std::runtime_error("Mensaje invalido para Lobby");
}
Lobby* Lobby::operator*(const std::vector<Lobby*>& args) {
    throw std::runtime_error("Mensaje invalido para Lobby");
}
Lobby* Lobby::operator+(const std::vector<Lobby*>& args) {
    throw std::runtime_error("Mensaje invalido para Lobby");
}
Lobby* Lobby::operator-(const std::vector<Lobby*>& args) {
    throw std::runtime_error("Mensaje invalido para Lobby");
}
Lobby* Lobby::operator/(const std::vector<Lobby*>& args) {
    throw std::runtime_error("Mensaje invalido para Lobby");
}
Lobby* Lobby::operator==(const std::vector<Lobby*>& args) {
    throw std::runtime_error("Mensaje invalido para Lobby");
}
Lobby* Lobby::operator!=(const std::vector<Lobby*>& args) {
    throw std::runtime_error("Mensaje invalido para Lobby");
}
Lobby* Lobby::modifyMutableValue(const std::vector<Lobby*>& args) {
    throw std::runtime_error("Mensaje invalido para Lobby");
}
Lobby* Lobby::mutableAsignation(const std::vector<Lobby*>& args) {
    throw std::runtime_error("Mensaje invalido para Lobby");
}

Lobby* Lobby::print(const std::vector<Lobby*>& args) {
    throw std::runtime_error("Mensaje invalido para Lobby");
}
