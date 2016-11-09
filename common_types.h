/*
 * common_types.h
 *
 *  Created on: 8 de nov. de 2016
 *      Author: kmoriell
 */

#ifndef COMMON_TYPES_H_
#define COMMON_TYPES_H_

#include <string>

#define END_MESSAGE '^'

// Mensajes de servidor
#define ERRORMESSAGE -1
#define OKMESSAGE 0x00
#define AVAILABLEMESSAGE 0x01

// Comandos de cliente
#define LOADCOMMAND 0x10
#define AVAILABLECOMMAND 0x11
#define NEWCOMMAND 0x12
#define DELETECOMMAND 0x13
#define CLOSECOMMAND 0x14

#define SENDCOMMAND 0x15

class command_t {
 private:
  size_t length;
  char command;
  std::string message;

 public:
  command_t(size_t length, char command, std::string message) : length(length), command(command), message(message){}
  command_t() {}

  /*
   * Este metodo devuelve en el parametro pasado el contenido
   * convertido a char* plano, para ser enviado por red.
   * Es responsabilidad de quien lo llama liberar la memoria.
   */
  void toString(char *command) {
    command = new char[length];
    memcpy(command, &length, sizeof(size_t));
    command[4] = this->command;
    memcpy(command + 5, message.c_str(), message.size());
  }

  /*
   * Este metodo carga el objeto con la cadena recibida.
   * len cuenta la longitud del mensaje total, teniendo en cuenta
   * el codigo de mensaje
   */
  void fromString(char *_message, size_t len) {
    length = len;
    command = _message[0];

    for (size_t i = 1; i < len; i++) {
      if (_message[i] != '\0')
        message.push_back(_message[i]);
    }
  }

  size_t getLength() const{
    return length;
  }

  std::string getMessage() const {
    return message;
  }

  char getCommand() const {
    return command;
  }
};



#endif /* COMMON_TYPES_H_ */
