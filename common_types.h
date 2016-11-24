#ifndef COMMON_TYPES_H_
#define COMMON_TYPES_H_

#include <string>

class command_t {
private:
	size_t length;
	char instr;
	std::string message;

public:
	command_t(size_t length, char command, std::string message) :
			length(length), instr(command), message(message) {
	}
	command_t() {
	} //todo verificar esto

	/*
	 * Este metodo devuelve en el parametro pasado el contenido
	 * convertido a char* plano, para ser enviado por red.
	 * Es responsabilidad de quien lo llama liberar la memoria.
	 */
	std::string toString() {
		std::string command;
		char *strLength = new char[sizeof(int) + 1];
		size_t length = htons(this->length);
		memcpy(strLength, &length, sizeof(int));

		//char *c_strLength = strLength.c_str();

		command += std::string(strLength);
		command += this->instr;
		command += message;
		/* memcpy(command, strLength.c_str(), strLengthSize);
		 command[strLengthSize] = this->instr;
		 memcpy(command + strLengthSize + 1, message.c_str(), message.size());
		 */
		delete[] strLength;
		return command;
	}

	size_t getLength() const {
		return length;
	}

	void setLength(const size_t len) {
		this->length = len;
	}

	std::string getMessage() const {
		return message;
	}

	void setMessage(const char* str) {
		message = std::string(str);
	}

	void setCommand(const char cmd) {
		this->instr = cmd;
	}

	char getCommand() const {
		return instr;
	}
};

#endif /* COMMON_TYPES_H_ */
