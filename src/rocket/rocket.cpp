
#include "rocket.h"
#include <algorithm>
#include <assert.h>
#include <iostream>

Rocket::Rocket() {
    this->stageCount = 0;
}

Rocket::Rocket(const Rocket& orig) {
}

Rocket::~Rocket() {
}

double Rocket::Mass() {
    double mass = 0;
    for (int i = 0; i < parts.size(); i++) {
        mass += parts[i]->mass;
    }
    return mass;
}

void Rocket::PartAdd(std::string partName) {
    this->PartAdd(partName, 0);
}

void Rocket::PartAdd(std::string partName, stage_t stage) {
    Part *part = PartFindByName(partName);
    if (NULL != part) {
        this->parts.push_back(part);
        this->stages.push_back(stage);
        this->stageCount = std::max(stage, this->stageCount);
    } else {
        std::cout << partName << std::endl;
        assert(NULL != part);
    }
}

part_count_t Rocket::PartCount() {
    return this->parts.size();
}

void Rocket::StageAsparagusSet(stage_t stage, bool _asparagus) {
    this->asparagus[stage] = _asparagus;
}

stage_t Rocket::StageCount() {
    return stageCount;
}

double Rocket::StageDryMass(stage_t stage) {
    double mass = 0;
    for (int i = 0; i < parts.size(); i++) {
        if (stage == stages[i]) {
            mass += parts[i]->dryMass;
        } else if (stages[i] < stage) {
            mass += parts[i]->mass;
        }
    }
    return mass;
}

double Rocket::StageIsp(stage_t stage) {
    double isp = 0;
    double thrust = 0;
    if (true == this->asparagus[stage]) {
        thrust += this->StageThrust(stage - 1);
        isp += (thrust * this->StageIsp(stage - 1));
    }
    for (int i = 0; i < parts.size(); i++) {
        if (stage == stages[i]) {
            isp += parts[i]->isp * parts[i]->thrust;
            thrust += parts[i]->thrust;
        }
    }
    if (0.0 == thrust) {
        return 0;
    }
    isp /= thrust;
    return isp;
}

double Rocket::StageMass(stage_t stage) {
    double mass = 0;
    for (int i = 0; i < parts.size(); i++) {
        if (stage >= stages[i]) {
            mass += parts[i]->mass;
        }
    }
    return mass;
}

double Rocket::StageThrust(stage_t stage) {
    double thrust = 0;
    if (true == this->asparagus[stage]) {
        thrust += this->StageThrust(stage - 1);
    }
    for (int i = 0; i < parts.size(); i++) {
        if (stage == stages[i]) {
            thrust += parts[i]->thrust;
        }
    }
    return thrust;
}
