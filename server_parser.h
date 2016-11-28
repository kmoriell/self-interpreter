#ifndef SERVER_PARSER_H_
#define SERVER_PARSER_H_

#include <string>

#include "server_object.h"
#include "server_virtualMachine.h"

class Parser {
private:
    /// Objeto sobre el que se ejecuta el script.
    Object* context;
    /// String del script a ejecutar
    std::string cad;
    /// Posicion de la cadena cad sobre la que está analizando el parser.
    uint32_t pCad;
    /// Modo debug
    bool debug = false;
    /// Cuando vale 1 se ejecuta el metodo receiveMessage
    /// Cada vez que se ingresa a un nuevo script incrementa en 1.
    int flagExecute;
    /// Máquina virtual del workspace
    VirtualMachine &vm;

public:
    /** Constructor
     * @param vm Máquina virtual
     * @param context Objeto sobre el que se ejecuta el script.
     *
     */
    Parser(VirtualMachine &vm, Object* context);

    /** Constructor por copia deshabilitado
     */
    Parser(const Parser&) = delete;
    /** Constructor por movimiento deshabilitado
     */
    Parser(Parser&&) = delete;
    /** Operador de asignacion deshabilitado
     */
    Parser& operator=(const Parser&) = delete;
    /** Operador de asignacion por moviemiento deshabilitado
     */
    Parser& operator=(Parser&&) = delete;

    std::vector<Object*> parse(std::string &cad);

private:
    std::vector<Object*> script();
    Object* expression();
    Object* expressionCP();
    Object* expressionP();
    Object* keywordMessage();
    Object* binaryMessage();
    Object* receiveMessage(Object* obj, std::string &strName,
            std::vector<Object*> &args);
    Object* unaryMessage();
    Object* receiver();
    bool slotList(Object* objContenedor);
    bool slotNameExtended(int &tipoSlot, std::string &strName);
    Object* constant();
    bool operador(std::string &strOperador);
    bool operadorSlot(std::string &strOperadorSlot);
    bool lowerKeyword(std::string &strLowerKeyword);
    bool capKeyword(std::string &strCapKeyword);

    void skipSpaces();
    bool isString(const std::string strMatch);

    bool isLowercaseLetter();
    bool isUppercaseLetter();
    bool isLetter();
    bool isSign();
    bool isDigit();
    bool isAlpha();

    //Devuelven los objetos, ya sea creandolos
    //o instanciandolos.
    Object* nilObj();
    Object* boolObj();
    Object* stringObj();
    Object* numberObj();
    Object* objectObj();
    Object* nameObj(Object* &context);

    bool nil();
    bool isTrue();
    bool isFalse();
    bool name(std::string &strName);
    std::string string();
    bool number(float &number);
};

#endif /* SERVER_PARSER_H_ */
