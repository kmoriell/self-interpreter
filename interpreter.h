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
#include "number.h"
#include "object.h"
#include "string.h"

class Interpreter {
 private:
  std::map<std::string, Object*> global_objects;
  Object* process(slot_t currentSlot, Object* object);
  Object* process_internal(opcode_t __opcode, slot_t currentSlot, Object* object);

 public:
  void createObject(std::string name);
  void setObjectAttributes(std::string name, std::map<std::string, Object*> attributes);
  void addSlot(std::string object, std::string slot_name, std::vector<std::string> );
  void call(std::string name, std::string method, std::vector<Object*> params);
  Object* getOperand(std::string instr, slot_t currentSlot, Object* object);
};



#endif /* INTERPRETER_H_ */
