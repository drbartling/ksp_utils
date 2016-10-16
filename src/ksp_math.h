/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   ksp_math.h
 * Author: ryanb
 *
 * Created on October 14, 2016, 10:13 PM
 */

#ifndef KSP_MATH_H
#    define KSP_MATH_H

/** Surface Gravity of Kerbin */
#    define KEE (9.81)

/**
 * dV = LN(Mi / Mf) * ISP * 9.81
 */
namespace DeltaV {
    double ComputeDeltaV(double massInitial, double massFinal, double isp);
    double ComputeMassInitial(double deltaV, double massFinal, double isp);
    double ComputeMassFinal(double deltaV, double massInitial, double isp);
    double ComputeIsp(double deltaV, double massInitial, double massFinal);
}

/**
 * TWR = Ft / M / G
 */
namespace TWR {
    double ComputeTWR(double thrust, double mass, double gee);
    double ComputeMass(double twr, double thrust, double gee);
}

#endif /* KSP_MATH_H */

