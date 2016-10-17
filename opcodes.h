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

/*#define MUL 0x0
#define ADD 0x1
#define RET 0x2
#define DEF 0x3
#define MOV 0x4
#define CALL 0x5
#define EXE 0xff*/

typedef struct {
  std::string method;
  std::vector<std::string> operands;
} opcode_t;

#endif /* OPCODES_H_ */
