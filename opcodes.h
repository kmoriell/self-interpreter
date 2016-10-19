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

typedef struct {
  std::string method;
  std::vector<std::string> operands;
} opcode_t;

#endif /* OPCODES_H_ */
