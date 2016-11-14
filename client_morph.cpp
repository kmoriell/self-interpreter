#include "client_morph.h"

#include <string>
#include <iostream>
#include <tuple>
#include <vector>

Morph::Morph() {
	clear();
}

void Morph::clear() {
	objName = std::string("ObjectName");
	codeSegment = std::string("codeSegment..");
	//Hay que verificar que no queden cosas colgadas al hacer el clear del vector
	slots = std::vector<slot_morph> { };
}

std::string Morph::getObjName() const {
	return objName;
}

std::string Morph::getCodeSegment() const {
	return codeSegment;
}

int Morph::getSlotsSize() const {
	return slots.size();
}

std::string Morph::getSlotName(int nSlot) const {
	return std::get<0>(slots.at(nSlot));
}

bool Morph::isNativeMethodSlot(int nSlot) const {
	return std::get<1>(slots.at(nSlot));
}

bool Morph::isMutableSlot(int nSlot) const {
	return std::get<2>(slots.at(nSlot));
}

bool Morph::isArgumentSlot(int nSlot) const {
	return std::get<3>(slots.at(nSlot));
}

bool Morph::isParentSlot(int nSlot) const {
	return std::get<4>(slots.at(nSlot));
}

std::string Morph::getSlotObjName(int nSlot) const {
	return std::get<5>(slots.at(nSlot));
}

std::string Morph::getSlotObjPreview(int nSlot) const {
	return std::get<6>(slots.at(nSlot));
}

void Morph::setObjName(std::string &cad) {
	objName = cad;
}

void Morph::setCodeSegment(std::string &cad) {
	codeSegment = cad;
}

void Morph::addSlot(std::string &slotName, bool isNativeMethod, bool isMutable,
		bool isArgument, bool isParent, std::string &objSlotName,
		std::string &objSlotPreview) {
	slot_morph slot = std::make_tuple(slotName, isNativeMethod, isMutable,
			isArgument, isParent, objSlotName, objSlotPreview);
	slots.push_back(slot);
}

void Morph::mostrar() {
	std::cout << "MORPH" << std::endl;
	std::cout << "ObjName: " << objName << std::endl;
	std::cout << "CodeSegment: " << codeSegment << std::endl;

	int i;
	for (i = 0; i < getSlotsSize(); i++) {
		std::cout << std::endl;
		std::cout << "N Slot: " << std::to_string(i) << std::endl;
		std::cout << "SlotName: " << getSlotName(i) << std::endl;
		std::cout << "isNativeMethod: " << isNativeMethodSlot(i) << std::endl;
		std::cout << "isMutable: " << isMutableSlot(i) << std::endl;
		std::cout << "isArgument: " << isArgumentSlot(i) << std::endl;
		std::cout << "isParent: " << isParentSlot(i) << std::endl;
		std::cout << "objSlotName: " << getSlotObjName(i) << std::endl;
		std::cout << "objSlotPreview: " << getSlotObjPreview(i) << std::endl;
	}
}

Morph::~Morph() {
	// TODO Auto-generated destructor stub
}

