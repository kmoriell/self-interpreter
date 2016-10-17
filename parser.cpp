/*
 * parser.cpp
 *
 *  Created on: 14 de oct. de 2016
 *      Author: kmoriell
 */

#include "parser.h"
#include "opcodes.h"
//#include "interpreter.h"
#include <sstream>

void Parser::parseText(std::string text) {
  std::istringstream iss(text);
  std::string object;
  std::string method_name;
  std::string x, instructions;

  iss >> std::noskipws;
  iss >> std::ws >> object >> std::ws >> method_name;

  while (iss >> std::skipws >> x) {
    instructions += x;
  }

}

void Parser::parseInstructions(std::string instructions) {
  std::istringstream iss(instructions);
  std::string x;
  std::string name;
  std::string line;

  while (iss >> std::skipws >> x) {
    if (x == "(") {
      openParenthesis = true;
      parenthesisCount++;
      line += x;
    } else if (x == "|") {
      pipesCount++;
      line += x;
    } else if (x == "=") {
      continue;
    } else {
      name = x;
    }
  }
}

void Parser::processAtom(std::string atom) {
  // traduzco por ejemplo: (x * x) + (y * y)
  std::istringstream iss(atom);
  std::string::size_type start, end;
  std::string operand, x;
  char sep;

  if ((start = atom.find('(')) != std::string::npos) {
    // Entonces tiene un parentesis
    if ((end = atom.find('(', start)) != std::string::npos) {
      std::string _atom = atom.substr(start + 1, atom.size() - end);
      processAtom(_atom);
    }
  } else {
    // Ya se que no tiene parentesis

    // Pongo todos los operandos en un vector de strings,
    // el primero es el que recibe el mensaje.
    // Si tiene 2 elementos es un mensaje unario
    // Si tiene 3 elementos es un mensaje binario
    // Si tiene mas de 3 es un mensaje n-ario.
    std::vector<std::string> operands;
    while (iss >> std::skipws >> x) {
      operands.push_back(x);
    }
    uint32_t countOfElements = operands.size();
    if (countOfElements == 2) {
      // Mensaje unario
      opcode_t oper;
      oper.oper = CALL;
      oper.operands.push_back(operands[1]);
    } else if (countOfElements == 3) {
      opcode_t oper;
      Lobby *_oper1 = new Lobby(operands[0]);
      Lobby *_oper2 = new Lobby(operands[2]);
      oper.oper = operands[1];
      oper.operands.push_back(_oper1);
      oper.operands.push_back(_oper2);
    }
  }

}

