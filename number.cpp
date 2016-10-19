#include "number.h"

Number::Number() {
    this->number = 0.0;
    _mutable = true;
}

Number::Number(float newNumber, bool _mutable) {
    this->number = newNumber;
    this->_mutable = _mutable;
}

Number::Number(const Number& _number) : Object((Object)*this) {
    this->number = _number.number;
    this->_mutable = _number._mutable;
}


Object* Number::print(const std::vector<Object*>& args) {
    std::string number_str = std::to_string(this->number);

    std::cout << number_str;
    return this;
}

Object* Number::operator=(const std::vector<Object*>& args) {
    if (this->number != 0.0 && !_mutable)
        throw std::runtime_error("Intentando modificar un objeto inmutable");
    Number* first = (Number*)args[0];
    this->number = first->number;
    return this;
}

Object* Number::operator*(const std::vector<Object*>& args) {
    Number* first = (Number*)args[0];
    this->number *= first->number;
    return this;
}

Object* Number::operator+(const std::vector<Object*>& args) {
    Number* first = (Number*)args[0];
    this->number += first->number;
    return this;
}

Object* Number::operator-(const std::vector<Object*>& args) {
    Number* first = (Number*)args[0];
    this->number -= first->number;
    return this;
}

Object* Number::operator/(const std::vector<Object*>& args) {
    Number* first = (Number*)args[0];
    this->number /= first->number;
    return this;
}

Object* Number::mutableAsignation(const std::vector<Object*>& args) {
    Number* first = (Number*)args[0];
    this->number = first->number;
    return this;
}


