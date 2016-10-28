
#include "catch.hpp"
#include "rocket/rocket.h"
#include "ksp_math.h"
#include <iostream>
#include <stdbool.h>

TEST_CASE("Example Rocket") {

    GIVEN("A Single Stage Booster") {
        Rocket booster;
        stage_t stage = 0;

        PartPayloadMassSet(6); 
        booster.PartAdd("Payload");
        // Munar Injection
        booster.PartAdd("FL-T800", stage);
        booster.PartAdd("TR-18A", stage);
        booster.PartAdd("LV-909", stage);
        stage++;
        for (int j = 0; j < 3; j++, stage++) {
            for (int i = 0; i < 2; i++) {
                if(j == 0) {
                    booster.PartAdd("LV-909", stage);
                }
                booster.PartAdd("TT-38K", stage);
                booster.PartAdd("FL-T400", stage);
                booster.PartAdd("Aerodynamic Nose Cone", stage);
                booster.StageAsparagusSet(stage, true);
            }
        }
        // LKO Insertion
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
                booster.PartAdd("TT-38K", stage);
                booster.PartAdd("LV-T30", stage);
                booster.PartAdd("FL-T800", stage);
                booster.PartAdd("FL-T800", stage);
                booster.PartAdd("Aerodynamic Nose Cone", stage);
                booster.PartAdd("Tail Fin", stage);
                booster.StageAsparagusSet(stage, true);
            }
        }

        // Start report
        stage_t stages = booster.StageCount() + 1;
        std::cout << "Stages: " << stages << "\r\n";

        // Stage report
        std::cout << "Stage \t";
        std::cout << "Mass-Tot \tMass-Stage \t";
        std::cout << "dV-Tot \tdV-Stage \t";
        std::cout << "TWR \t";
        std::cout << "\r\n";
        double rocketDeltaV = 0;
        double rocketMass = 0;
        for(int i = stages - 1; i >= 0; i--) {

            double stageMass = booster.StageMass(i);
            rocketMass += stageMass;

            double stageDeltaV = DeltaV::ComputeDeltaV(
                    booster.StageMass(i),
                    booster.StageDryMass(i),
                    booster.StageIsp(i));
            rocketDeltaV += stageDeltaV;

            double twr = TWR::ComputeTWR(
                    booster.StageThrust(i),
                    booster.StageMass(i),
                    KEE);

            std::cout << i << " \t";
            std::cout << rocketMass << " \t\t" << stageMass << " \t\t";
            std::cout << (int)rocketDeltaV << " \t" << (int)stageDeltaV << " \t\t";
            std::cout <<  twr << " \t";
            std::cout << "\r\n";
        }
        std::cout << std::endl;

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
    }
}
