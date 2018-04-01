#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include "normal.h"
#include "normal.cpp"
#include "q1.h"

using namespace std;
using namespace normal;

Option::Option(double K, double T, double sigma, double r) : K(K), T(T), sigma(sigma), r(r) {
}

double Option::getBinomialTreeValue(double s, int N){
        double deltaT = T/N;
        double up = exp(sigma * sqrt(deltaT));

        double p0 = (up - exp(-r * deltaT)) / (up*up - 1);
        double p1 = exp(-r * deltaT) - p0;

        // initial values at time T
        vector<double> p(N+1);
        for (int i = 0; i < N + 1; i++) {
                double spot = s * pow(up, 2 * i - N);
                p[i] = getExerciseValue(spot, T);
                if (p[i] < 0) {
                        p[i] = 0;
                }
        }

        // move to earlier times
        double t = T;
        for (int j = N - 1; j >= 0; j--) {
                t = t - deltaT;
                for (int i = 0; i < j + 1; i++) {
                        double spot  = s * pow(up, 2*i - j);
                        double exercise = getExerciseValue(spot, t);
                        p[i] = p0 * p[i+1] + p1 * p[i]; // binomial value

                        // check for early exercise
                        if (p[i] < exercise) {
                                p[i] = exercise;
                        }
                }
        }

        return p[0];
}

double Option::getDelta(double s){
        double h = 0.01;
        double x = s;
        return (getValue(x + h) + getValue(x - h)) / (2 * h);
}

double Option::getGamma(double s){
        double h = 0.01;
        double x = s;
        return (getValue(x - h) - 2 * getValue(h) + getValue(x + h)) / (h * h);
}

double Option::getTheta(double T){
        double h = 0.01;
        double x = T;
        return (getValue(x + h) + getValue(x - h)) / (2 * h);
}

double Option::getRho(double r){
        double h = 0.001;
        double x = r;
        return (getValue(x + h) + getValue(x - h)) / (2 * h);
}

double Option::getVega(double sigma){
        double h = 0.001;
        double x = sigma;
        return (getValue(x + h) + getValue(x - h)) / (2 * h);
}

EuropeanOption::EuropeanOption(double K, double T, double sigma, double r) : Option(K, T, sigma, r) {
}

double EuropeanOption::estimateError(double s, int N){
        return getBinomialTreeValue(s, N) - getBlackScholesValue(s);
}

AmericanOption::AmericanOption(double K, double T, double sigma, double r) : Option(K, T, sigma, r){
}

EuropeanCall::EuropeanCall(double K, double T, double sigma, double r) : EuropeanOption(K, T, sigma, r){
}

double EuropeanCall::getExerciseValue(double s, double t){
        if(t != T) {
                return 0;
        }
        else {
                double diff = s - K;
                if(diff > 0) {
                        return diff;
                }
                else{
                        return 0;
                }
        }
}

double EuropeanCall::getValue(double s){
        return getBlackScholesValue(s);
}

double EuropeanCall::getBlackScholesValue(double s){
        double d1 = 1/(sigma * sqrt(T)) * (log(s/K) + (r + sigma*sigma/2)*T);
        double d2 = d1 - sigma * sqrt(T);
        return N(d1) * s - N(d2) * K * exp(-r * T);
}

AmericanCall::AmericanCall(double K, double T, double sigma, double r) : AmericanOption(K, T, sigma, r){
}

double AmericanCall::getExerciseValue(double s, double t){
        double diff = s - K;
        if (diff > 0) {
                return diff;
        }
        else {
                return 0;
        }
}

double AmericanCall::getValue(double s){
        return getBinomialTreeValue(s, 250);
}


double AmericanCall::getBlackScholesValue(double s){
        double d1 = 1/(sigma * sqrt(T)) * (log(s/K) + (r + sigma*sigma/2)*T);
        double d2 = d1 - sigma * sqrt(T);
        return N(d1) * s - N(d2) * K * exp(-r * T);
}

double AmericanCall::estimateCorrectedValue(double s, int N){
        return getBinomialTreeValue(s, N) - EuropeanCall(K, T, sigma, r).estimateError(s, N);
}

EuropeanPut::EuropeanPut(double K, double T, double sigma, double r) : EuropeanOption(K, T, sigma, r){
}

double EuropeanPut::getExerciseValue(double s, double t){
        if(t != T) {
                return 0;
        }
        else {
                double diff =  K - s;
                if (diff > 0) {
                        return diff;
                }
                else {
                        return 0;
                }
        }
}

double EuropeanPut::getValue(double s){
        return getBlackScholesValue(s);
}

double EuropeanPut::getBlackScholesValue(double s){
        double d1 = 1/(sigma * sqrt(T)) * (log(s/K) + (r + sigma*sigma/2)*T);
        double d2 = d1 - sigma * sqrt(T);
        return N(-d2) * K * exp(-r * T) - N(-d1) * s;
}

AmericanPut::AmericanPut(double K, double T, double sigma, double r) : AmericanOption(K, T, sigma, r){
}

double AmericanPut::getExerciseValue(double s, double t){
        double diff =  K - s;
        if (diff > 0) {
                return diff;
        }
        else {
                return 0;
        }
}

double AmericanPut::getValue(double s){
        return getBinomialTreeValue(s, 250);
}

double AmericanPut::getBlackScholesValue(double s){
        double d1 = 1/(sigma * sqrt(T)) * (log(s/K) + (r + sigma*sigma/2)*T);
        double d2 = d1 - sigma * sqrt(T);
        return N(-d2) * K * exp(-r * T) - N(-d1) * s;
}

double AmericanPut::estimateCorrectedValue(double s, int N){
        return getBinomialTreeValue(s, N) - EuropeanPut(K, T, sigma, r).estimateError(s, N);
}
