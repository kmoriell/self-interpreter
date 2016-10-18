#include "number.h"

Number::Number() {
    this->number = 0.0;
}

Lobby* Number::print(const std::vector<Lobby*>& args) {
    std::string number_str = std::to_string(this->number);

    std::cout << number_str;
    return this;
}

Lobby* Number::operator=(const std::vector<Lobby*>& args) {
    if (this->number != 0.0)
        throw std::runtime_error("Intentando modificar un objeto inmutable");
    Number* first = (Number*)args[0];
    this->number = first->number;
    return this;
}

Lobby* Number::operator*(const std::vector<Lobby*>& args) {
    Number* first = (Number*)args[0];
    this->number *= first->number;
    return this;
}

Lobby* Number::operator+(const std::vector<Lobby*>& args) {
    Number* first = (Number*)args[0];
    this->number += first->number;
    return this;
}

Lobby* Number::operator-(const std::vector<Lobby*>& args) {
    Number* first = (Number*)args[0];
    this->number -= first->number;
    return this;
}

Lobby* Number::operator/(const std::vector<Lobby*>& args) {
    Number* first = (Number*)args[0];
    this->number /= first->number;
    return this;
}

Lobby* Number::mutableAsignation(const std::vector<Lobby*>& args) {
    Number* first = (Number*)args[0];
    this->number = first->number;
    return this;
}


