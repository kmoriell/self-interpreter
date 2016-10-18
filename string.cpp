#include "string.h"

String::String() {
    this->_internalString = "";
}

String::String(std::string _string) {
    this->_internalString = _string;
}

String::~String() {
}

Lobby* String::print (const std::vector<Lobby *> &args) {
    std::cout << this->_internalString;
    return this;
}

Lobby* String::operator=(const std::vector<Lobby*>& args) {
    if (_internalString.size() == 0) {
        this->_mutable = false;
        this->_internalString = ((String*)args[0])->_internalString;
        return this;
    } else
        throw std::runtime_error("Intentando modificar un objecto inmutable");
}

Lobby* String::mutableAsignation(const std::vector<Lobby*>& args) {
    if (!this->_mutable)
        throw std::runtime_error("Intentando modificar un objecto inmutable");
    this->_mutable = true;
    this->_internalString = ((String*)args[0])->_internalString;
    return this;
}
