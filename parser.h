/*
 * parser.h
 *
 *  Created on: 14 de oct. de 2016
 *      Author: kmoriell
 */

#ifndef PARSER_H_
#define PARSER_H_

#include <string>

class Parser {
 private:
  void parseInstructions(std::string instructions);
  void processAtom(std::string atom);

 public:
  void parseText(std::string text);
};




#endif /* PARSER_H_ */
