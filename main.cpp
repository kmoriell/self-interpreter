#include <iostream>
#include "interpreter.h"
#include "object.h"

int main() {
  /*
   *  void addSlot(std::string object, std::string slot_name, std::vector<std::string> args, bool _mutable,
   std::vector<opcode_t> code);
   */

  Interpreter interpreter;
  interpreter.createObject("punto");
  std::vector<std::string> args;
  // Creo el slot x
  std::vector<opcode_t> slot_x;

  opcode_t punto1;
  punto1.receiver = "0";

  slot_x.push_back(punto1);

  // Creo el slot y
  std::vector<opcode_t> slot_y;

  opcode_t y_code;
  y_code.receiver = "1";

  slot_y.push_back(y_code);

  interpreter.addSlot("punto", "x", args, true, slot_x);
  interpreter.addSlot("punto", "y", args, true, slot_y);

  std::vector<opcode_t> parameters;
  opcode_t print;
  print.message = "print";

  parameters.push_back(print);

  interpreter.call("punto", "x", parameters);

  // pruebo square_norm = (|| ((x*x)+(y*y)). ).
  std::vector<opcode_t*> emptyVector;

  opcode_t op1 = {"y", "", emptyVector};
  opcode_t op2 = {"y", "*", std::vector<opcode_t*> {&op1} };
  opcode_t op3 = {"", "+", std::vector<opcode_t*> {&op2} };
  opcode_t op4 = {"x", "", emptyVector};
  opcode_t op5 = {"x", "*", std::vector<opcode_t*> {&op4, &op3} };

  std::vector<opcode_t> slot_square_norm = {op1,op2,op3,op4, op5};

  interpreter.addSlot("punto","square_norm", args, false, slot_square_norm);
  interpreter.call("punto", "square_norm", parameters);

  return 0;
}
