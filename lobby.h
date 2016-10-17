/*
 * lobby.h
 *
 *  Created on: 14 de oct. de 2016
 *      Author: kmoriell
 */

#ifndef LOBBY_H_
#define LOBBY_H_

#include <string>
#include "opcodes.h"

typedef struct {
  std::map<std::string, void*> arguments;
  std::map<std::string, void*> localVariables;
  std::vector<opcode_t> instructions;
} slot_t;

class Lobby {
public:
	  typedef Lobby*(*delegate)(std::vector<Lobby*>);
 private:
  std::string name;
  bool _mutable;
  std::map<std::string, slot_t> slots;
  std::map<std::string, delegate> methods;

 public:
  void setName(std::string newName);
  void _AddSlots(std::string name, slot_t newSlot);
  void _RemoveSlots(std::string name);
  void setMutable(bool state);
  bool getMutable();

  slot_t getSlot(std::string name);
  delegate getMethod(std::string name);

  Lobby* clone();
  virtual Lobby* print();
  virtual ~Lobby();
  Lobby* collect();

  // Sobrecarga de operadores y definicion de nuevas operaciones
  Lobby& operator=(const Lobby& inmutableValue);
  Lobby& modifyMutableValue(const Lobby& mutableValue);
  Lobby& mutableAsignation(const Lobby& mutableValue);


};



#endif /* LOBBY_H_ */
