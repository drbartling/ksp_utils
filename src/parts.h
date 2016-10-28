
#ifndef PARTS_H
#    define PARTS_H

#    include <string>

typedef struct {
    std::string name;
    double mass;
    double dryMass;
    double thrust; ///< tons
    double isp; ///< seconds
    double atm; ///< thrust, ISP modifier when at sea level
} Part;

Part *PartFindByName(std::string name);

void PartPayloadMassSet(double mass);

#endif /* PARTS_H */
