
#include "catch.hpp"
#include "rocket/rocket.h"
#include "ksp_math.h"
#include <iostream>
#include <stdbool.h>

TEST_CASE("Example Rocket") {

    GIVEN("A Single Stage Booster") {
        Rocket booster;
        stage_t stage = 0;
        booster.PartAdd("TR-18A", stage);
        for (int i = 0; i < 2; i++) {
            booster.PartAdd("FL-T800", stage);
        }
        for (int i = 0; i < 2; i++) {
            booster.PartAdd("Tail Fin", stage);
        }
        booster.PartAdd("LV-T45", stage);
        stage++;
        for (int j = 0; j < 3; j++, stage++) {
            for (int i = 0; i < 2; i++) {
                booster.PartAdd("LV-T30", stage);
                booster.PartAdd("FL-T800", stage);
                booster.PartAdd("FL-T800", stage);
                booster.PartAdd("Aerodynamic Nose Cone", stage);
                booster.PartAdd("Tail Fin", stage);
                booster.StageAsparagusSet(stage, true);
            }
        }

        stage_t stages = booster.StageCount() + 1;
        std::cout << "Stages: " << stages << "\r\n";

        double deltaV = 0;
        for (int i = 0; i < stages; i++) {
            deltaV += DeltaV::ComputeDeltaV(
                    booster.StageMass(i),
                    booster.StageDryMass(i),
                    booster.StageIsp(i));
        }
        std::cout << "Delta V: " << deltaV << "\r\n";

        double twr = TWR::ComputeTWR(booster.StageThrust(stages - 1), booster.StageMass(stages - 1), KEE);
        std::cout << "TWR: " << twr << "\r\n";

        double dVToOrbit = 3400;
        dVToOrbit *= 1.1; // Some spare + some to get back down.
        double maxPayloadToOrbit = DeltaV::ComputePayload(
                dVToOrbit, booster.StageMass(0), booster.StageDryMass(0), booster.StageIsp(0));
        std::cout << "Payload to Orbit: " << maxPayloadToOrbit << "\r\n";

        double maxPayload = TWR::ComputeMass(1.2, booster.StageThrust(stages - 1), KEE);
        maxPayload -= booster.StageMass(stages - 1);
        std::cout << "Max Payload: " << maxPayload << "\r\n";

        double deltaVWithMaxPayload = 0;
        for (int i = 0; i < stages; i++) {
            deltaVWithMaxPayload += DeltaV::ComputeDeltaV(
                    booster.StageMass(i) + maxPayload,
                    booster.StageDryMass(i) + maxPayload,
                    booster.StageIsp(i));
        }
        std::cout << "dV with Max Payload: " << deltaVWithMaxPayload << "\r\n";

        double payload = 16;
        double deltaVWithPayload = 0;
        for (int i = 0; i < stages; i++) {
            deltaVWithPayload += DeltaV::ComputeDeltaV(
                    booster.StageMass(i) + payload,
                    booster.StageDryMass(i) + payload,
                    booster.StageIsp(i));
        }
        std::cout << "dV with Payload: " << deltaVWithPayload << "\r\n";
    }
}
