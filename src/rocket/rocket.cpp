
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

double Rocket::StageMass(stage_t stage) {
    double mass = 0;
    for (int i = 0; i < parts.size(); i++) {
        if (stage >= stages[i]) {
            mass += parts[i]->mass;
        }
    }
    return mass;
}