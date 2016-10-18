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
#include "lobby.h"
#include "number.h"
#include "string.h"

class Interpreter {
 private:
  std::map<std::string, Lobby*> global_objects;
  Lobby* process(slot_t currentSlot, Lobby* object);
  Lobby* process_internal(opcode_t __opcode, slot_t currentSlot, Lobby* object);

 public:
  void createObject(std::string name);
  void setObjectAttributes(std::string name, std::map<std::string, Lobby*> attributes);
  //void setObjectMethods(std::string name, std::map<std::string, std::vector<opcode_t> > instructions, std::map<std::string, Lobby*> parameters);
  void addSlot(std::string object, std::string slot_name, slot_t newSlot);
  void call(std::string name, std::string method, std::vector<Lobby*> params);
  Lobby* getOperand(std::string instr, slot_t currentSlot, Lobby* object);
};



#endif /* INTERPRETER_H_ */
