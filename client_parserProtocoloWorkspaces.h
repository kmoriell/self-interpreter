#ifndef PARSER_PROTOCOLO_WORKSPACES_H_
#define PARSER_PROTOCOLO_WORKSPACES_H_

#include <string>
#include <vector>

/** Esta clase se encarga de parsear los mensajes que lleguen al
 *  cliente con el comando OK_MSG_SELECT_WKS y cargar el vector de
 *  workspaces con la información obtenida.
 */
class ParserProtocoloWorkspaces {
private:
	std::vector<std::string> &workspaces;
	std::string &cad;
	int pCad = 0;

public:
	/** Constructor
	 * @param workspaces lista de nombres de workspaces.
	 * @param cad cadena que se va a parsear según protocolo
	 */
	ParserProtocoloWorkspaces(std::vector<std::string> &workspaces,
			std::string &cad);

	/** Constructor por copia deshabilitado
	 */
	ParserProtocoloWorkspaces(const ParserProtocoloWorkspaces&) = delete;

	/** Constructor por movimiento deshabilitado
	 */
	ParserProtocoloWorkspaces(ParserProtocoloWorkspaces&&) = delete;

	/** Operador de asignacion deshabilitado
	 */
	ParserProtocoloWorkspaces& operator=(const ParserProtocoloWorkspaces&) = delete;

	/** Operador de asignacion por moviemiento deshabilitado
	 */
	ParserProtocoloWorkspaces& operator=(ParserProtocoloWorkspaces&&) = delete;
private:
	/** Captura el siguiente campo de la cadena cad utilizando como separador
	 * el caracter especial de protocolo CHAR_SEPARADOR
	 */
	std::string getCampo();
};

#endif /* PARSE_RPROTOCOLO_WORKSPACES_H_ */
