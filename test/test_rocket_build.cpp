
#include "catch.hpp"
#include "rocket/rocket.h"
#include "ksp_math.h"
#include <iostream>

TEST_CASE("Example Rocket") {

    GIVEN("A Single Stage Booster") {
        Rocket booster;
        stage_t stage = 0;
        booster.PartAdd("MK1 Command Pod", stage);
        booster.PartAdd("MK1 Crew Cabin", stage);
        for (int i = 0; i < 6; i++) {
            booster.PartAdd("FL-T800", stage);
        }
        for (int i = 0; i < 4; i++) {
            booster.PartAdd("Tail Fin", stage);
            booster.PartAdd("Airbrake", stage);
        }
        for (int i = 0; i < 2; i++) {
            booster.PartAdd("LV-T30", stage);
            booster.PartAdd("Aerodynamic Nose Cone", stage);
            booster.PartAdd("MK2-R", stage);
            booster.PartAdd("MK12-R", stage);
            booster.PartAdd("Delta-Deluxe Winglet", stage);
        }
        booster.PartAdd("LV-T45", stage);

        double deltaV = DeltaV::ComputeDeltaV(booster.StageMass(0), booster.StageDryMass(0), booster.StageIsp(0));
        std::cout << "Delta V: " << deltaV << "\r\n";

        double twr = TWR::ComputeTWR(booster.StageThrust(0), booster.StageMass(0), KEE);
        std::cout << "TWR: " << twr << "\r\n";

        double maxPayload = TWR::ComputeMass(1.2, booster.StageThrust(0), KEE);
        maxPayload -= booster.StageMass(0);
        std::cout << "Max Payload: " << maxPayload << "\r\n";

        double dVToOrbit = 3400;
        dVToOrbit *= 1.1; // Some spare + some to get back down.
        double maxPayloadToOrbit = DeltaV::ComputePayload(
                dVToOrbit, booster.StageMass(0), booster.StageDryMass(0), booster.StageIsp(0));
        std::cout << "Payload to Orbit: " << maxPayloadToOrbit << "\r\n";
    }
}