/*
 * interpreter.h
 *
 *  Created on: 13 de oct. de 2016
 *      Author: kmoriell
 */

#ifndef INTERPRETER_H_
#define INTERPRETER_H_

#include <vector>
#include <map>
#include <string>
#include <stdexcept>
#include <cstdlib>
#include <cctype>
#include "opcodes.h"
#include "object.h"

class Interpreter {
 private:
  std::map<std::string, Object*> global_objects;

 public:
  void createObject(std::string name);
  void addSlot(std::string object, std::string slot_name, std::vector<std::string> args, bool _mutable,
               std::vector<opcode_t> code);
  void call(std::string name, std::string message, std::vector<opcode_t> args);
};



#endif /* INTERPRETER_H_ */
