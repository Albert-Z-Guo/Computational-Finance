#ifndef Q2_H
#define Q2_H

using namespace std;

// declare a WeightTracker class
class WeightTracker {
      protected:
          vector<double> weights;

      public:
          WeightTracker(const vector<double>& weights); // constructor

          double dotProduct(const vector<double>& values);
};


// declare a CholeskyDecomposition class
class CholeskyDecomposition {
      public:
          CholeskyDecomposition(); // constructor

          Matrix decompose(const Matrix& m);
};

// declare an Euity class
class Equity {
      protected:
            double r;
            double vol;
            vector<double> weights;

      public:
          Equity(double r, double vol, const vector<double>& weights); // constructor

          double nextReturn(double dt, const vector<double>& gaussians);
};

#endif
