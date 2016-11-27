#ifndef PARSER_PROTOCOLO_MORPH_H_
#define PARSER_PROTOCOLO_MORPH_H_

#include <string>
#include <vector>
#include "client_morph.h"

/** Esta clase se encarga de parsear los mensajes que lleguen al
 *  cliente con el comando OK_MSG_MORPH y cargar el objeto Morph
 *  con la información obtenida.
 */
class ParserProtocoloMorph {
private:
	Morph &morph;
	std::string &cad;
	int pCad = 0;

public:
	/** Constructor
	 * @param morph Objeto que contiene la información para dibujar
	 * en la ventana MorphWindow.
	 * @param cad cadena que se va a parsear según protocolo
	 */
	ParserProtocoloMorph(Morph &morph, std::string &cad);

	/** Constructor por copia deshabilitado
	 */
	ParserProtocoloMorph(const ParserProtocoloMorph&) = delete;

	/** Constructor por movimiento deshabilitado
	 */
	ParserProtocoloMorph(ParserProtocoloMorph&&) = delete;

	/** Operador de asignacion deshabilitado
	 */
	ParserProtocoloMorph& operator=(const ParserProtocoloMorph&) = delete;

	/** Operador de asignacion por moviemiento deshabilitado
	 */
	ParserProtocoloMorph& operator=(ParserProtocoloMorph&&) = delete;

private:
	/** Captura el siguiente campo de la cadena cad utilizando como separador
	 * el caracter especial de protocolo CHAR_SEPARADOR
	 */
	std::string getCampo();
};

#endif /* PARSE_RPROTOCOLO_MORPH_H_ */
