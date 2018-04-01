#ifndef Q1_H
#define Q1_H

// declare an Option class
class Option {
      protected:
          double K; // strike
          double T; // time-to-maturity
          double sigma; // stock volatility
          double r; // risk-free rate

      public:
          Option(double K, double T, double sigma, double r); // constructor

          double getBinomialTreeValue(double s, int N);
          double getDelta(double s);
          double getGamma(double s);
          double getTheta(double T);
          double getRho(double r);
          double getVega(double sigma);

          // declare virtual methods
          virtual double getExerciseValue(double s, double t) = 0;
          virtual double getBlackScholesValue(double s) = 0;
          virtual double getValue(double s) = 0;
};

// declare a European Option class derived from the Option class
class EuropeanOption : public Option {
      public:
          EuropeanOption(double K, double T, double sigma, double r); // constructor
          double estimateError(double s, int N);
};

// declare a American Option class derived from the Option class
class AmericanOption : public Option {
      public:
          AmericanOption(double K, double T, double sigma, double r); // constructor
          virtual double estimateCorrectedValue(double s, int N) = 0; // pure virtual method

};

// declare an European Put class derived from the Option class
class EuropeanPut : public EuropeanOption {
      public:
          EuropeanPut(double K, double T, double sigma, double r); // constructor
          double getExerciseValue(double s, double t);
          double getBlackScholesValue(double s);
          double getValue(double s);
};

// declare an European Call class derived from the Option class
class EuropeanCall : public EuropeanOption {
      public:
          EuropeanCall(double K, double T, double sigma, double r); // constructor
          double getExerciseValue(double s, double t);
          double getBlackScholesValue(double s);
          double getValue(double s);
};

// declare an American Put class derived from the Option class
class AmericanPut : public AmericanOption {
      public:
          AmericanPut(double K, double T, double sigma, double r); // constructor
          double getExerciseValue(double s, double t);
          double getBlackScholesValue(double s);
          double getValue(double s);
          double estimateCorrectedValue(double s, int N);
};

// declare an American Call class derived from the Option class
class AmericanCall : public AmericanOption {
      public:
          AmericanCall(double K, double T, double sigma, double r); // constructor
          double getExerciseValue(double s, double t);
          double getBlackScholesValue(double s);
          double getValue(double s);
          double estimateCorrectedValue(double s, int N);
};

#endif
