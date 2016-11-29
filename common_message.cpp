#include "common_message.h"
#include <string>

Message::Message(size_t length, char command, std::string message) :
            length(length), instr(command), message(message) {
}
Message::Message() {
}

std::string Message::toString() {
    std::string command;
    char *strLength = new char[sizeof(int) + 1];
    size_t length = htons(this->length);
    memcpy(strLength, &length, sizeof(int));

    command += std::string(strLength);
    command += this->instr;
    command += message;

    delete[] strLength;
    return command;
}

size_t Message::getLength() const {
    return length;
}

void Message::setLength(const size_t len) {
    this->length = len;
}

std::string Message::getMessage() const {
    return message;
}

void Message::setMessage(const char* str) {
    message = std::string(str);
}

void Message::setCommand(const char cmd) {
    this->instr = cmd;
}

char Message::getCommand() const {
    return instr;
}
