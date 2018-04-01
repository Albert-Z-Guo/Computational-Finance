#include <iostream>
#include <fstream>
#include "q1.h"

using namespace std;

int main()
{
        ofstream myfile;
        myfile.open ("main_Q1.txt");
        myfile << "option,type,strike,spot,bs_value,value,binomialValue,correctedValue" << endl;

        {

                double spot = 100;
                double strike = 90;
                double riskFreeRate = 0.15;
                double sigma = 0.375;
                double T = 1;
                int N = 100;

                EuropeanCall option(strike, T, sigma, riskFreeRate);
                double V = option.getValue(spot);
                double bs_V = option.getBlackScholesValue(spot);
                double binomial = option.getBinomialTreeValue(spot, N);
                double corrected = option.estimateError(spot, N);
                myfile << "1,EC," << strike << "," << spot << "," << bs_V << "," << V << "," << binomial << "," << corrected << endl;
        }

        {

                double spot = 100;
                double strike = 95;
                double riskFreeRate = 0.05;
                double sigma = 0.4;
                double T = 0.5;
                int N = 100;

                AmericanCall option(strike, T, sigma, riskFreeRate);
                double V = option.getValue(spot);
                double bs_V = option.getBlackScholesValue(spot);
                double binomial = option.getBinomialTreeValue(spot, N);
                double corrected = option.estimateCorrectedValue(spot, 250);

                myfile << "2,AC," << strike << "," << spot << "," << bs_V << "," << V << "," << binomial << "," << corrected << endl;
        }

        {

                double spot = 100;
                double strike = 105;
                double riskFreeRate = 0.15;
                double sigma = 0.25;
                double T = 0.25;
                int N = 250;

                AmericanPut option(strike, T, sigma, riskFreeRate);
                double V = option.getValue(spot);
                double bs_V = option.getBlackScholesValue(spot);
                double binomial = option.getBinomialTreeValue(spot, N);
                double corrected = option.estimateCorrectedValue(spot, 250);

                myfile << "3,AP," << strike << "," << spot << "," << bs_V << "," << V << "," << binomial << "," << corrected << endl;
        }

        {

                double spot = 100;
                double strike = 95;
                double riskFreeRate = 0.1;
                double sigma = 0.15;
                double T = 0.25;
                int N = 250;

                EuropeanPut option(strike, T, sigma, riskFreeRate);
                double V = option.getValue(spot);
                double bs_V = option.getBlackScholesValue(spot);
                double binomial = option.getBinomialTreeValue(spot, N);
                double corrected = option.estimateError(spot, N);

                myfile << "4,EP," << strike << "," << spot << "," << bs_V << "," << V << "," << binomial << "," << corrected << endl;
        }

        myfile.close();

        return 0;
}
