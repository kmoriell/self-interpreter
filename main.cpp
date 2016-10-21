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
  std::vector<opcode_t> slot_punto1;

  opcode_t punto1;
  punto1.receiver = "0";

  slot_punto1.push_back(punto1);

  // Creo el slot y
  std::vector<opcode_t> slot_y;

  opcode_t y_code;
  y_code.receiver = "1";

  slot_y.push_back(y_code);

  interpreter.addSlot("punto", "x", args, true, slot_punto1);
  interpreter.addSlot("punto", "y", args, true, slot_y);

  std::vector<opcode_t> parameters;
  opcode_t print;
  print.message = "print";

  interpreter.call("punto", "x", parameters);

  return 0;
}
