#include <ctime>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include "matrix.h"
#include "mtrand.h"
#include "q2.h"

using namespace std;

class EquityPrices {
protected:
vector<double> prices;
vector<Equity*> equities;
public:
EquityPrices(vector<double> vectR, vector<double> vectVol, Matrix& correlationMatrix)  : generate(true), drand((int)time(0))
{
								Matrix decomp = CholeskyDecomposition().decompose(correlationMatrix);


								for (unsigned int i = 0; i < decomp.size(); i++) {
																prices.push_back(1.0);
																Equity* equity = new Equity(vectR[i], vectVol[i], decomp[i]);
																equities.push_back(equity);
								}
}

virtual ~EquityPrices() {
								for (vector<Equity*>::iterator it = equities.begin(); it != equities.end(); it++) {
																delete *it;
								}
}

void reset() {
								for (vector<double>::iterator it = prices.begin(); it != prices.end(); it++) {
																*it = 1.0;
								}
}

const vector<double>& stepPrices(double dt) {
								vector<double> gaussians;
								// simulate uncorrelated gaussians
								for (unsigned int i = 0; i < equities.size(); i++) {
																gaussians.push_back(generateGaussianNoise(0, 1));
								}

								// update prices
								for (unsigned int i = 0; i < equities.size(); i++) {
																double r = equities[i]->nextReturn(dt, gaussians);
																prices[i] *= exp(r);
								}

								return prices;

}

const vector<double>& getPrices() {
								return prices;
}

private:
double z0, z1;
bool generate;
MTRand drand;

double generateGaussianNoise(double mu, double sigma)
{
								const double epsilon = 1e-10;
								const double two_pi = 2.0*3.14159265358979323846;


								generate = !generate;

								if (!generate)
																return z1 * sigma + mu;

								double u1, u2;
								do
								{
																u1 = drand();
																u2 = drand();
								} while (u1 <= epsilon);

								z0 = sqrt(-2.0 * log(u1)) * cos(two_pi * u2);
								z1 = sqrt(-2.0 * log(u1)) * sin(two_pi * u2);
								return z0 * sigma + mu;
}

};

int main() {
								ofstream myfile;
								myfile.open("main_Q2.txt");

								double portfolioWeights[] = { 1000.0, 200.0, 500.0, 1250.0, 1000.0 };
								vector<double> vectPortfolioWeights(portfolioWeights, portfolioWeights + sizeof(portfolioWeights) / sizeof(portfolioWeights[0]));

								double equityReturns[] = { 0.01, 0.05, 0.12,  0.075, 0.08 };
								vector<double> vectEquityReturns(equityReturns, equityReturns + sizeof(equityReturns) / sizeof(equityReturns[0]));

								double equityVol[] = { 0.15, 0.05, 0.11, 0.2, 0.3 };
								vector<double> vectEquityVol(equityVol, equityVol + sizeof(equityVol) / sizeof(equityVol[0]));

								int numRows = 5;
								const double correlations[][5] = { { 1, 0.891876304, 0.734238211, 0.820605646, 0.893830411 },
																																											{0.891876304, 1, 0.639630441, 0.678266278, 0.734325215},
																																											{0.734238211, 0.639630441, 1, 0.476690371, 0.553114695},
																																											{ 0.820605646, 0.678266278, 0.476690371, 1, 0.698639297},
																																											{ 0.893830411, 0.734325215, 0.553114695, 0.698639297, 1} };

								Matrix corr;
								for (int i = 0; i < numRows; i++) {
																vector<double> vectRow(correlations[i], correlations[i] + numRows);
																corr.push_back(vectRow);
								}


								Matrix cholesky = CholeskyDecomposition().decompose(corr);
								myfile << "Cholesky Decomposition is:" << endl;
								for (unsigned int i = 0; i < cholesky.size(); i++) {
																for (unsigned int j = 0; j < cholesky.size(); j++) {
																								myfile << cholesky[i][j] << " ";
																}
																myfile << endl;
								}


								WeightTracker Portfolio(vectPortfolioWeights);
								EquityPrices ep(vectEquityReturns, vectEquityVol, corr);

								double portfolioSum = 0;
								double portfolioCount = 0;
								double dt = 1.0 / 12.0;


								for (int i = 0; i < 100000; i++) {
																ep.reset();
																int steps = 0;
																for (double t = 0; fabs(t - 1) > 1e-5; t += dt) {
																								ep.stepPrices(dt);
																								steps++;
																}
																portfolioSum += Portfolio.dotProduct(ep.getPrices());
																portfolioCount++;

																if ((i + 1) % 10000 == 0) {
																								myfile << "Expected Portfolio Value [" << (i + 1) << "] : " << (portfolioSum / portfolioCount) << endl;
																}
								}

								portfolioSum /= portfolioCount;

								myfile << endl << "Expected Portfolio Value " << portfolioSum << endl;

								myfile.flush();
								myfile.close();

								return 0;
}
