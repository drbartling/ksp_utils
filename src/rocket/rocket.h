
#ifndef ROCKET_H
#    define ROCKET_H

#    include <stdint.h>
#    include <string>
#    include "parts.h"
#    include <vector>

typedef int16_t part_count_t;
typedef int16_t stage_t;

class Rocket {
public:
    Rocket();
    Rocket(const Rocket& orig);
    virtual ~Rocket();

    double Mass();

    void PartAdd(std::string partName);
    void PartAdd(std::string partName, stage_t stage);
    part_count_t PartCount();

    void StageAsparagusSet(stage_t stage, bool asparagus);
    stage_t StageCount();
    double StageDryMass(stage_t stage);
    double StageIsp(stage_t stage);
    double StageMass(stage_t stage);
    double StageThrust(stage_t stage);

private:
    bool asparagus[100] = {false};
    std::vector<Part*> parts;
    std::vector<stage_t> stages;
    stage_t stageCount;
};

#endif /* ROCKET_H */

