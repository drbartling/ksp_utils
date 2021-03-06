
#include "ksp_math.h"
#include <math.h>

namespace DeltaV {

    double ComputeDeltaV(double massInitial, double massFinal, double isp) {
        return log(massInitial / massFinal) * KEE * isp;
    }

    double ComputeMassInitial(double deltaV, double massFinal, double isp) {
        return exp(deltaV / KEE / isp) * massFinal;
    }

    double ComputeMassFinal(double deltaV, double massInitial, double isp) {
        return massInitial / exp(deltaV / KEE / isp);
    }

    double ComputeIsp(double deltaV, double massInitial, double massFinal) {
        return deltaV / (log(massInitial / massFinal) * KEE);
    }

    double ComputePayload(double deltaV, double massInitial, double massFinal, double isp) {
        return (massInitial - exp(deltaV / isp / KEE) * massFinal) / (exp(deltaV / isp / KEE) - 1);
    }
}

namespace TWR {

    double ComputeTWR(double thrust, double mass, double gee) {
        return thrust / mass / gee;
    }

    double ComputeMass(double twr, double thrust, double gee) {
        return thrust / twr / gee;
    }
}