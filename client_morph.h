#ifndef CLIENT_MORPH_H_
#define CLIENT_MORPH_H_

#include <string>
#include <tuple>
#include <vector>

class Morph {
public:
    /*
     Elementos de slot_t
     pos	tipo		variable
     0	std::string	nombreSlot
     1	bool		esMetodoNativo
     2	bool		esMutable
     3	bool		esArgument
     4	bool		esParent
     5	std::string	nombreObjSlot
     6	std::string	previewObjSlot
     * */
    typedef std::tuple<std::string, bool, bool, bool, bool, std::string,
            std::string> slot_morph;

private:
    std::string objName;
    std::string codeSegment;
    std::vector<slot_morph> slots;

public:
    Morph();
    Morph(const Morph&) = delete;
    Morph(Morph&&) = delete;
    Morph& operator=(const Morph&) = delete;
    void clear();

    //Getters
    std::string getObjName() const;
    std::string getCodeSegment() const;
    int getSlotsSize() const;
    std::string getSlotName(int nSlot) const;
    bool isNativeMethodSlot(int nSlot) const;
    bool isMutableSlot(int nSlot) const;
    bool isArgumentSlot(int nSlot) const;
    bool isParentSlot(int nSlot) const;
    std::string getSlotObjName(int nSlot) const;
    std::string getSlotObjPreview(int nSlot) const;

    //Setters
    void setObjName(std::string &cad);
    void setCodeSegment(std::string &cad);
    void addSlot(std::string &slotName, bool isNativeMethod, bool isMutable,
            bool isArgument, bool isParent, std::string &objSlotName,
            std::string &objSlotPreview);

    void mostrar();
};

#endif /* CLIENT_MORPH_H_ */
