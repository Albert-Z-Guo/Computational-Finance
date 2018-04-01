#include <iostream>
#include <cstdlib>
#include <cmath>
#include <vector>
#include "mtrand.h"
#include "mtrand.cpp"
#include "Matrix.h"
#include "q2.h"

using namespace std;

WeightTracker::WeightTracker(const vector<double>& weights) : weights(weights) {
}

double WeightTracker::dotProduct(const vector<double>& values){
        double sum = 0;
        for (int i = 0; i < values.size(); i++) {
                sum += weights[i] * values[i];
        }
        return sum;
}

CholeskyDecomposition::CholeskyDecomposition() {
}

Matrix CholeskyDecomposition::decompose(const Matrix& m){
        int len = m.size();

        // initialize all Matrix elements to 0
        Matrix l;
        for (int i = 0; i < len; i++) {
                vector<double> temp;
                for(int j = 0; j < len; j++)
                        temp.push_back(0);
                l.push_back(temp);
        }

        for (int i = 0; i < len; i++) {
                for (int k = 0; k < (i+1); k++) {
                        double sum = 0;
                        for(int j = 0; j < k; j++) {
                                sum += l[i][j] * l[k][j];
                        }
                        l[i][k] = (i == k) ? sqrt(m[i][i] - sum) : (1.0 / l[k][k] * (m[i][k] - sum));
                }
        }
        return l;
}

Equity::Equity(double r, double vol, const vector<double>& weights) : r(r), vol(vol), weights(weights) {
}

double Equity::nextReturn(double dt, const vector<double>& gaussians){
        double sigma =  vol * pow(dt, 0.5);
        double mu = r * dt  - 1/2 * pow(sigma, 2);
        double Z = WeightTracker(weights).dotProduct(gaussians);
        double nextReturn = mu + sigma * Z;
        return nextReturn;
}
