#include <iostream>
#include "q1.h"

using namespace std;

int main(){
        double spot = 50;
        double strike = 55;
        double riskFreeRate = 0.03;
        double sigma = 0.2;
        double T = 0.5;

        cout << "Spot: " << spot << endl;
        cout << "Strike: " << strike << endl;
        cout << "Risk-free Rate: " << riskFreeRate << endl;
        cout << "Sigma: " << sigma << endl;
        cout << "Time to Maturity: " << T << endl;
        cout << endl;

        AmericanCall AmericanCall(strike, T, sigma, riskFreeRate);
        cout << "For American Call:" << endl;
        cout << "Delta: " << AmericanCall.getDelta(spot) << endl;
        cout << "Gamma: " << AmericanCall.getGamma(spot) << endl;
        cout << "Theta: " << AmericanCall.getTheta(T) << endl;
        cout << "Rho: " << AmericanCall.getRho(riskFreeRate) << endl;
        cout << "Vega: " << AmericanCall.getVega(sigma) << endl;
        cout << endl;

        AmericanPut AmericanPut(strike, T, sigma, riskFreeRate);
        cout << "For American Put:" << endl;
        cout << "Delta: " << AmericanPut.getDelta(spot) << endl;
        cout << "Gamma: " << AmericanPut.getGamma(spot) << endl;
        cout << "Theta: " << AmericanPut.getTheta(T) << endl;
        cout << "Rho: " << AmericanPut.getRho(riskFreeRate) << endl;
        cout << "Vega: " << AmericanPut.getVega(sigma) << endl;
        cout << endl;

        EuropeanCall EuropeanCall(strike, T, sigma, riskFreeRate);
        cout << "For European Call:" << endl;
        cout << "Delta: " << EuropeanCall.getDelta(spot) << endl;
        cout << "Gamma: " << EuropeanCall.getGamma(spot) << endl;
        cout << "Theta: " << EuropeanCall.getTheta(T) << endl;
        cout << "Rho: " << EuropeanCall.getRho(riskFreeRate) << endl;
        cout << "Vega: " << EuropeanCall.getVega(sigma) << endl;
        cout << endl;

        EuropeanPut EuropeanPut(strike, T, sigma, riskFreeRate);
        cout << "For European Put:" << endl;
        cout << "Delta: " << EuropeanPut.getDelta(spot) << endl;
        cout << "Gamma: " << EuropeanPut.getGamma(spot) << endl;
        cout << "Theta: " << EuropeanPut.getTheta(T) << endl;
        cout << "Rho: " << EuropeanPut.getRho(riskFreeRate) << endl;
        cout << "Vega: " << EuropeanPut.getVega(sigma) << endl;
}
