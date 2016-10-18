/*
 * lobby.h
 *
 *  Created on: 14 de oct. de 2016
 *      Author: kmoriell
 */

#ifndef LOBBY_H_
#define LOBBY_H_

#include <string>
#include <stdexcept>
#include <map>
#include "opcodes.h"

typedef struct {
  std::map<std::string, void*> arguments;
  std::map<std::string, void*> localVariables;
  std::vector<opcode_t> instructions;
} slot_t;

class Lobby {
public:
  typedef Lobby* (Lobby::*delegate)(const std::vector<Lobby*>&);
 protected:
  std::string name;
  bool _mutable;
  std::map<std::string, slot_t> slots;
  std::map<std::string, delegate> methods;

 public:
  Lobby();
  // Constructor copia
  Lobby(const Lobby& _lobby);
  void setName(std::string newName);
  void _AddSlots(std::string name, slot_t newSlot);
  void _RemoveSlots(std::string name);
  void setMutable(bool state);
  bool getMutable() const;

  slot_t getSlot(std::string name) const;
  delegate getMethod(std::string name) const;

  Lobby* clone(const std::vector<Lobby*>& args);
  Lobby* collect();

  // Sobrecarga de operadores y definicion de nuevas operaciones
  virtual Lobby* operator=(const std::vector<Lobby*>& args);
  virtual Lobby* operator*(const std::vector<Lobby*>& args);
  virtual Lobby* operator+(const std::vector<Lobby*>& args);
  virtual Lobby* operator-(const std::vector<Lobby*>& args);
  virtual Lobby* operator/(const std::vector<Lobby*>& args);
  virtual Lobby* operator==(const std::vector<Lobby*>& args);
  virtual Lobby* operator!=(const std::vector<Lobby*>& args);
  virtual Lobby* modifyMutableValue(const std::vector<Lobby*>& args);
  virtual Lobby* mutableAsignation(const std::vector<Lobby*>& args);

  virtual Lobby* print(const std::vector<Lobby*>& args);
  virtual ~Lobby();


};



#endif /* LOBBY_H_ */
