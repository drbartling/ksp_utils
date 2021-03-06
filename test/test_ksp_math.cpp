
#include "catch.hpp"
#include "ksp_math.h"
#include <math.h>

TEST_CASE("Delta V Equations", "[Math]") {

    SECTION("Solving for Delta-V") {
        REQUIRE(0 == DeltaV::ComputeDeltaV(1e3, 1e3, 100));
        REQUIRE(100.0 == (DeltaV::ComputeDeltaV(exp(2), exp(1), (100.0 / 9.81))));
    }

    SECTION("Solving for Initial Mass") {

        WHEN("Delta-V is 0") {
            double deltaV = 0.0;
            double massFinal = exp(1);
            double isp = 100;

            SECTION("Initial mass will equal final mass") {
                REQUIRE(massFinal == DeltaV::ComputeMassInitial(deltaV, massFinal, isp));
            }
        }

        WHEN("Delta-V is 100") {

            AND_WHEN("isp is equal to 100/9.81") {
                double deltaV = 100.0;
                double massFinal = exp(1);
                double isp = 100.0 / 9.81;
                REQUIRE(exp(2) == DeltaV::ComputeMassInitial(deltaV, massFinal, isp));
            }
        }
    }

    SECTION("Solving for Final Mass") {

        WHEN("Delta-V is 0") {
            double deltaV = 0.0;
            double massInitial = exp(1);
            double isp = 100;

            SECTION("Final mass will equal initial mass") {
                REQUIRE(massInitial == DeltaV::ComputeMassFinal(deltaV, massInitial, isp));
            }
        }

        WHEN("Delta-V is 100") {
            double deltaV = 100.0;

            AND_WHEN("isp is equal to 100/9.81") {
                double isp = 100.0 / 9.81;

                THEN("Final Mass will equal Initial mass / e") {
                    double massInitial = exp(2);
                    double massFinal = massInitial / exp(1);
                    REQUIRE(massFinal == Approx(DeltaV::ComputeMassFinal(deltaV, massInitial, isp)));
                }
            }
        }
    }

    SECTION("Solving for ISP") {

        WHEN("Delta-V is 0") {
            double deltaV = 0.0;
            double massInitial = exp(2);
            double massFinal = exp(1);
            REQUIRE(0.0 == DeltaV::ComputeIsp(deltaV, massInitial, massFinal));
        }

        WHEN("Final Mass is equal to e^1") {
            double massFinal = exp(1);

            AND_WHEN("Initial Mass is equal to e^2") {
                double massInitial = exp(2);

                THEN("ISP will equal deltaV / 9.81") {
                    double deltaV = 100.0;
                    REQUIRE(deltaV / 9.81 == DeltaV::ComputeIsp(deltaV, massInitial, massFinal));
                }
            }
        }
    }
}

TEST_CASE("TWR Equations", "[Math]") {

    SECTION("Solving for TWR") {

        WHEN("Thrust is 0") {
            double thrust = 0.0;
            double mass_kg = 10;
            double gee_mpss = 10;

            THEN("TWR will be 0") {
                REQUIRE(0.0 == TWR::ComputeTWR(thrust, mass_kg, gee_mpss));
            }
        }

        WHEN("Mass and Gee are 1") {
            double mass_kg = 1, gee_mpss = 1;

            THEN("TWR will equal thrust") {
                double thrust = 10;
                REQUIRE(thrust == TWR::ComputeTWR(thrust, mass_kg, gee_mpss));
            }
        }

        WHEN("With these thrust, mass, and local gravity parameters") {
            double thrust = 100, mass_kg = 5, gee_mpss = 10;

            THEN("TWR will be 2") {
                double expectedTwr = 2;
                REQUIRE(expectedTwr == TWR::ComputeTWR(thrust, mass_kg, gee_mpss));
            }
        }
    }

    SECTION("Solving for mass") {

        WHEN("Thrust is 0") {
            double thrust = 0, twr = 1.2, gee_mpss = 10;

            THEN("Mass will be 0") {
                double mass = 0;
                REQUIRE(mass == TWR::ComputeMass(twr, thrust, gee_mpss));
            }
        }

        WHEN("TWR is computed") {
            double thrust = 6e3, mass = 4e3, gee_mpss = 10;
            double twr = TWR::ComputeTWR(thrust, mass, gee_mpss);

            THEN("Mass should equal previous value") {
                REQUIRE(mass == TWR::ComputeMass(twr, thrust, gee_mpss));
            }
        }
    }
}
