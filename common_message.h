#ifndef COMMON_TYPES_H_
#define COMMON_TYPES_H_

#include <string>
#include <netinet/in.h>
#include <cstring>

class Message {
private:
    size_t length;
    char instr;
    std::string message;

public:
    Message(size_t length, char command, std::string message);
    Message();

    /** Este metodo devuelve el objeto convertido a std::string.
     *
     */
    std::string toString();

    /** Devuelve la longitud del mensaje
     *
     */
    size_t getLength() const;

    /** Fija la longitud del mensaje
     * @param len nueva longitud
     */
    void setLength(const size_t len);

    /** Devuelve el texto del mensaje-
     *
     */
    std::string getMessage() const;

    /** Fija el text del mensaje.
     * @param str nuevo mensaje
     */
    void setMessage(const char* str);

    /** Fija el comando del mensaje.
     * @param cmd nuevo comando.
     */
    void setCommand(const char cmd);

    /** Devuelve el comando del mensaje.
     *
     */
    char getCommand() const;
};

#endif /* COMMON_TYPES_H_ */
