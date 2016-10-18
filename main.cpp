#include <iostream>
#include "interpreter.h"
#include "lobby.h"
#include "number.h"

int main() {
    slot_t square_norm;
    opcode_t code;
    code.operands.push_back("x");
    code.operands.push_back("x");
    code.method = "*";

    opcode_t _code;
    _code.operands.push_back("y");
    _code.operands.push_back("y");
    _code.method = "*";

    opcode_t __code;
    __code.operands.push_back("x");
    __code.operands.push_back("y");
    __code.method = "+";

    std::vector<opcode_t> instructions;
    instructions.push_back(code);
    instructions.push_back(_code);
    instructions.push_back(__code);
    square_norm.instructions =instructions;

    // slot x <- 0
    slot_t slot_x;
    opcode_t mutable1;
    mutable1.method = "<-";
    mutable1.operands = std::vector<std::string> { "x", "0"};

    slot_x.instructions = std::vector<opcode_t> {mutable1};

    // slot y <- 1
    slot_t slot_y;
    opcode_t mutable2;
    mutable2.method = "<-";
    mutable2.operands = std::vector<std::string> { "y", "1"};
    slot_y.instructions = std::vector<opcode_t> {mutable2};

    // pruebo un print
    slot_t slot_print;
    opcode_t _print;
    _print.method = "print";
    _print.operands = std::vector<std::string> { "'hola mundo'"};
    slot_print.instructions = std::vector<opcode_t> {_print};

    Interpreter interpreter;
    interpreter.createObject("punto");
    //interpreter.addSlot("punto", "square_norm", square_norm);
    //interpreter.addSlot("punto", "x", slot_x);
    //interpreter.addSlot("punto", "y", slot_y);
    interpreter.addSlot("punto", "print", slot_print);
    std::vector<Lobby*> parameters;
    //interpreter.call("punto", "square_norm", parameters);
    interpreter.call("punto", "print", parameters);

    return 0;
}
