
#include "catch.hpp"
#include "rocket/rocket.h"
#include <iostream>

TEST_CASE("Add first part to rocket", "[parts]") {

    GIVEN("A new Rocket") {
        Rocket testRocket;

        THEN("Part count will be 0") {
            REQUIRE(0 == testRocket.PartCount());
        }

        THEN("Stage count will be 0") {
            REQUIRE(0 == testRocket.StageCount());
        }

        WHEN("First part is added") {
            testRocket.PartAdd("LV-T45");

            THEN("Part count will be 1") {
                REQUIRE(1 == testRocket.PartCount());
            }
        }
    }
}

TEST_CASE("Add parts to stages", "[parts][stages]") {

    GIVEN("A new Rocket") {
        Rocket testRocket;

        WHEN("Parts are added to stage 1") {
            stage_t stage = 1;
            testRocket.PartAdd("LV-T30", stage);
            testRocket.PartAdd("FL-T400", stage);

            THEN("Stage count will be 1") {
                REQUIRE(1 == testRocket.StageCount());
            }
        }

        WHEN("Parts are added to stage 2") {
            stage_t stage = 2;
            testRocket.PartAdd("TR-18A", stage);
            testRocket.PartAdd("LV-T30", stage);
            testRocket.PartAdd("FL-T800", stage);

            AND_WHEN("Parts are added to stage 1") {
                stage = 1;
                testRocket.PartAdd("TR-18A", stage);

                THEN("Stage count will be 2") {
                    REQUIRE(2 == testRocket.StageCount());
                }
            }
        }
    }
}

TEST_CASE("Mass Increases as Parts are added", "[parts][mass]") {

    GIVEN("A new rocket") {
        Rocket testRocket;
        stage_t stage = 0;

        THEN("Mass will be 0") {
            REQUIRE(0 == testRocket.Mass());
        }

        WHEN("Parts are added to stage 0") {
            testRocket.PartAdd("MK1 Command Pod", stage);
            double mass = 0.84;
            REQUIRE(mass == testRocket.Mass());

            testRocket.PartAdd("MK16 Parachute", stage);
            mass += 0.1;
            REQUIRE(mass == testRocket.Mass());
        }
    }
}

TEST_CASE("Stage mass", "[parts][mass][stage]") {

    GIVEN("a new rocket") {
        Rocket testRocket;
        stage_t stage = 0;

        THEN("Stage 0 mass will be 0") {
            REQUIRE(0 == testRocket.StageMass(stage));
        }

        WHEN("Parts are added to stage 0") {
            testRocket.PartAdd("MK1 Command Pod", stage);
            double massCommandPod = 0.84;

            THEN("Stage 0 mass will increase") {
                REQUIRE(massCommandPod == testRocket.StageMass(stage));
            }

            AND_WHEN("Parts are added to stage 1") {
                stage = 1;
                double massDecoupler = 0.05;
                testRocket.PartAdd("TR-18A", stage);

                THEN("Stage 0 mass doesn't change") {
                    REQUIRE(massCommandPod == testRocket.StageMass(0));
                }

                AND_THEN("Stage 1 mass will increase and include stage 0 mass") {
                    double stageMass = massCommandPod + massDecoupler;
                    REQUIRE(stageMass == testRocket.StageMass(1));
                }
            }
        }
    }
}

TEST_CASE("Stage Dry Mass", "[parts][mass][stage]") {

    GIVEN("a new rocket") {
        Rocket testRocket;
        stage_t stage = 0;

        THEN("Stage 0 dry mass will be 0") {
            REQUIRE(0 == testRocket.StageDryMass(stage));
        }

        WHEN("Stage 0 has a fuel tank") {
            double dryMass = 0;
            testRocket.PartAdd("MK16 Parachute", stage);
            dryMass += 0.1;
            testRocket.PartAdd("MK1 Command Pod", stage);
            dryMass += 0.84;
            testRocket.PartAdd("FL-T400", stage);
            dryMass += 0.25;
            testRocket.PartAdd("LV-909", stage);
            dryMass += 0.5;

            THEN("Stage 0 dry mass will be the mass of the parts without fuel") {
                REQUIRE(dryMass + 2 == testRocket.StageMass(stage));
                REQUIRE(dryMass == testRocket.StageDryMass(stage));
            }

            AND_WHEN("Stage 1 has a fuel tank") {
                stage = 1;
                double dryMass = testRocket.StageMass(0);
                testRocket.PartAdd("TR-18A", stage);
                dryMass += 0.05;
                testRocket.PartAdd("FL-T800", stage);
                dryMass += 0.5;
                testRocket.PartAdd("LV-T45", stage);
                dryMass += 1.5;

                THEN("Stage 1 Dry mass will be stage 0's mass + stage 1's part's dry mass ") {
                    REQUIRE(dryMass == testRocket.StageDryMass(stage));
                }
            }
        }
    }
}

TEST_CASE("Computing Stage ISP", "[parts][stage][isp]") {

    GIVEN("a new rocket") {
        Rocket testRocket;
        stage_t stage = 0;

        THEN("Stage 0 ISP will be 0") {
            REQUIRE(0 == testRocket.StageIsp(stage));
        }

        WHEN("Stage 0 has a motor") {

            double isp = 345;
            testRocket.PartAdd("LV-909", stage);

            THEN("Stage 0 ISP will equal the ISP of the motor") {
                REQUIRE(isp == testRocket.StageIsp(stage));
            }

            AND_WHEN("A motor is added to stage 1") {
                stage = 1;
                testRocket.PartAdd("LV-T30", stage);
                isp = 310;

                THEN("Stage 1 ISP will equal the ISP of the motor in stage 1") {
                    REQUIRE(isp == testRocket.StageIsp(stage));
                }

                AND_WHEN("The same motor is added a second time") {
                    testRocket.PartAdd("LV-T30", stage);

                    THEN("The ISP will remain the same") {
                        REQUIRE(isp == testRocket.StageIsp(stage));
                    }

                    AND_WHEN("A motor with a different ISP is added") {
                        testRocket.PartAdd("LV-T45", stage);

                        THEN("The ISP will be the average ISP of the motors weighted by thrust") {
                            isp = (310.0 * 240.0) + (310.0 * 240.0) + (320.0 * 215.0);
                            isp /= (240.0 + 240.0 + 215.0);
                            REQUIRE(isp == testRocket.StageIsp(stage));
                        }
                    }
                }
            }
        }
    }
}

TEST_CASE("Computing stage thrust") {

    GIVEN("a new rocket") {
        Rocket testRocket;
        stage_t stage = 0;

        THEN("Stage 0 ISP will be 0") {
            REQUIRE(0 == testRocket.StageThrust(stage));
        }

        WHEN("Stage 0 has a motor") {
            double thrust = 60;
            testRocket.PartAdd("LV-909", stage);

            THEN("Stage 0 thrust will equal the thrust of the motor") {
                REQUIRE(thrust == testRocket.StageThrust(stage));
            }

            AND_WHEN("A motor is added to stage 1") {
                stage = 1;
                testRocket.PartAdd("LV-T30", stage);
                thrust = 240;

                THEN("Stage 1 thrust will equal the thrust of the motor in stage 1") {
                    REQUIRE(thrust == testRocket.StageThrust(stage));
                }

                AND_WHEN("Another motor is added to stage 1") {
                    testRocket.PartAdd("LV-T45", stage);
                    thrust += 215;

                    THEN("The thrust will equal the sum of the two motor thrusts") {
                        REQUIRE(thrust == testRocket.StageThrust(stage));
                    }
                }
            }
        }
    }
}
