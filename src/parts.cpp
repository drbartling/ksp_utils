
#include "parts.h"

Part partList[] = {
    // Name, Mass, Dry Mass, thrust, isp, atm
    {"FL-T400", 2.25, 0.25, 0, 0},
    {"FL-T800", 4.5, 0.5, 0, 0},
    {"LV-T30", 1.25, 1.25, 240, 310, 265 / 310},
    {"LV-T45", 1.5, 1.5, 215, 320, 250 / 320},
    {"LV-909", 0.5, 0.5, 60, 345, 85 / 345},
    {"MK1 Command Pod", 0.84, 0.84, 0, 0},
    {"MK16 Parachute", 0.1, 0.1, 0, 0},
    {"TR-18A", 0.05, 0.05, 0, 0},
};

Part *PartFindByName(std::string name) {
    for (int i = 0; i < (sizeof (partList) / sizeof (partList[0])); i++) {
        if (name == partList[i].name) {
            return &partList[i];
        }
    }
    return NULL;
}
