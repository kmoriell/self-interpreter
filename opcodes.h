/*
 * opcodes.h
 *
 *  Created on: 13 de oct. de 2016
 *      Author: kmoriell
 */

#ifndef OPCODES_H_
#define OPCODES_H_

#include <vector>
#include <string>

class opcode_t;

class opcode_t {
 public:
  std::string receiver;
  std::string message;
  std::vector<opcode_t*> args;
};

#endif /* OPCODES_H_ */
