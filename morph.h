#ifndef MORPH_H_
#define MORPH_H_

#include <string>
#include <iostream>
#include <tuple>
#include <vector>

class Morph {
public:
	/*
	Elementos de slot_t
	pos	tipo		variable
	0	std::string	nombreSlot
	1	bool		esMutable
	2	bool		esArgument
	3	bool		esParent
	4	std::string	nombreObjSlot
	5	std::string	previewObjSlot
	 * */
	typedef std::tuple<std::string, bool, bool, bool, std::string, std::string> slot_morph;
	Morph();
	void clear();

	//Getters
	std::string getObjName() const;
	std::string getCodeSegment() const;
	int getSlotsSize() const;
	std::string getSlotName(int nSlot) const;
	bool isMutableSlot(int nSlot) const;
	bool isArgumentSlot(int nSlot) const;
	bool isParentSlot(int nSlot) const;
	std::string getSlotObjName(int nSlot) const;
	std::string getSlotObjPreview(int nSlot) const;

	//Setters
	void setObjName(std::string &cad);
	void setCodeSegment(std::string &cad);
	void addSlot(std::string &slotName, bool isMutable, bool isArgument, bool isParent, std::string &objSlotName, std::string &objSlotPreview);

	void mostrar();

	virtual ~Morph();

private:
	std::string objName;
	std::string codeSegment;
	std::vector<slot_morph> slots;
};

#endif /* MORPH_H_ */
