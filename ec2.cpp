#include <iostream>
#include <cmath>
#include "q1.h"

using namespace std;

int main(){
        double spot = 125;
        double riskFreeRate = 0.15;
        double sigma = 0.15;
        double T = 2;

        cout << "Spot: " << spot << endl;
        cout << "Strike: 100-150" << endl;
        cout << "Risk-free Rate: " << riskFreeRate << endl;
        cout << "Sigma: " << sigma << endl;
        cout << "Time to Maturity: " << T << endl;
        cout << endl;

        double difference;
        double maxDifference = 0;
        double maxDifferenceStrike = 0;

        for (int i = 100; i < 151; i++) {
                double strike = i;

                cout << "Current Strike: " << strike << endl;

                AmericanPut AmericanPut(strike, T, sigma, riskFreeRate);
                EuropeanPut EuropeanPut(strike, T, sigma, riskFreeRate);

                difference = abs(EuropeanPut.getValue(spot) - AmericanPut.getValue(spot));

                if (difference > maxDifference) {
                        maxDifference = difference;
                        maxDifferenceStrike = strike;
                }

                cout << "American Put Value: " << AmericanPut.getValue(spot) << endl;
                cout << "European Put Value: " << EuropeanPut.getValue(spot) << endl;
                cout << endl;
        }

        cout << "Greatest Price Difference (American Put vs. European Put): " << maxDifference << endl;
        cout << "Happens at Stike: " << maxDifferenceStrike << endl;
        cout << "American options are more expensive because American option "
                "gives the same rights (to exercise early) as a European option, and more." << endl;
        cout << "This result can be proved by no-arbitrage principle or the monotonicity theorem." << endl;
        cout << "Reference: Chapter 7 Options of 'An Introduction to Quantitative Finance' "
                "1st Edition by Stephen Blyth" << endl;

}
