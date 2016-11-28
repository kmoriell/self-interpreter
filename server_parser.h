#ifndef SERVER_PARSER_H_
#define SERVER_PARSER_H_

#include <string>

#include "server_object.h"
#include "server_virtualMachine.h"

/** Es la clase encargada de parsear scripts en código self y de indicarle
 * a la maquina virtual (VM) que objetos y mensajes se deben emitir
 * en consecuencia.
 */
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

    /** Cuando vale 1 se ejecuta el metodo receiveMessage
     * Cada vez que se ingresa a un nuevo script incrementa en 1.
     */
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

    /** Inicia la secuencia de parseo del script en código self
     * @param cad código self
     */
    std::vector<Object*> parse(std::string &cad);

private:
    /** Esta es la función más importante del parser, se encarga de decidir
     * que objetos deben ser clonados antes de aplicarles un recv_message.
     * Para ello valida si son:
     * data objects: (objetos primivitos o que tengan codeSegment vacio).
     * method objects: son aquellos que no son data objects e incluye a los
     * metodos nativos.
     * Los métodos nativos son un caso especial ya que algúnos requieren de la
     * clonación como los operadores binarios y hay otros que no la requieren.
     *
     */

    Object* receiveMessage(Object* obj, std::string &strName,
            std::vector<Object*> &args);

    /// Valida si en la cadena continua un script
    std::vector<Object*> script();
    /// Valida si en la cadena continua una expression
    Object* expression();
    /// Valida si en la cadena continua una expressionCP
    Object* expressionCP();
    /// Valida si en la cadena continua una expressionP
    Object* expressionP();
    /// Valida si en la cadena continua un keyword message
    Object* keywordMessage();
    /// Valida si en la cadena continua un binary message
    Object* binaryMessage();
    /// Valida si en la cadena continua un unary message
    Object* unaryMessage();
    /// Valida si en la cadena continua un receiver
    Object* receiver();
    /// Valida si en la cadena continua un slotList
    bool slotList(Object* objContenedor);
    /// Valida si en la cadena continua un slotNameExtended
    bool slotNameExtended(int &tipoSlot, std::string &strName);
    /// Valida si en la cadena continua un constant
    Object* constant();
    /// Valida si en la cadena continua un operador
    bool operador(std::string &strOperador);
    /// Valida si en la cadena continua un operadorSlot
    bool operadorSlot(std::string &strOperadorSlot);
    /// Valida si en la cadena continua un lowerKeyword
    bool lowerKeyword(std::string &strLowerKeyword);
    /// Valida si en la cadena continua un capKeyword
    bool capKeyword(std::string &strCapKeyword);

    /// Saltea los espacios
    void skipSpaces();
    /// Valida si el string a continuación de la cadena es el buscado.
    bool isString(const std::string strMatch);
    /// Valida si en la cadena continua una letra minuscula
    bool isLowercaseLetter();
    /// Valida si en la cadena continua una letra mayuscula
    bool isUppercaseLetter();
    /// Valida si en la cadena continua una letra
    bool isLetter();
    /// Valida si en la cadena continua un signo + -
    bool isSign();
    /// Valida si en la cadena continua un digito
    bool isDigit();
    /// Valida si en la cadena continua un digito o una letra
    bool isAlpha();

    //Devuelven los objetos, ya sea creandolos
    //o instanciandolos.
    /** Valida si en la cadena continua un nil obj y si es asi le pide a la
     * máquina virtual que lo cree.
     *
     */
    Object* nilObj();
    /** Valida si en la cadena continua un bool obj y si es asi le pide a la
     * máquina virtual que lo cree.
     *
     */
    Object* boolObj();
    /** Valida si en la cadena continua un string obj y si es asi le pide a la
     * máquina virtual que lo cree.
     *
     */
    Object* stringObj();
    /** Valida si en la cadena continua un number obj y si es asi le pide a la
     * máquina virtual que lo cree.
     *
     */
    Object* numberObj();
    /** Valida si en la cadena continua un objeto y si es asi le pide a la
     * máquina virtual que cree un objeto vacío al cúal luego se le cargarán
     * los slots.
     *
     */
    Object* objectObj();
    /** Valida si en la cadena continua un name y si es asi se pide un lookup
     * de ese objeto para recuperarlo y devolverlo.
     *
     */
    Object* nameObj(Object* &context);

    /// Valida si en la cadena continua un nil
    bool nil();
    /// Valida si en la cadena continua un true
    bool isTrue();
    /// Valida si en la cadena continua un false
    bool isFalse();
    /// Valida si en la cadena continua un name
    bool name(std::string &strName);
    /// Valida si en la cadena continua un string
    std::string string();
    /// Valida si en la cadena continua un number
    bool number(float &number);
};

#endif /* SERVER_PARSER_H_ */
