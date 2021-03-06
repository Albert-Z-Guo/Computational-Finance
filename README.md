# Computational-Finance
## C++ Programming Project

- Constructed Option class hierarchy of American and European calls and puts.
- Computed [Black Scholes](https://en.wikipedia.org/wiki/Black%E2%80%93Scholes_model) and [Binomial Tree](https://en.wikipedia.org/wiki/Binomial_options_pricing_model) valuations.
- Computed Option price sensitivities to the Spot prices (the “[Greeks](https://en.wikipedia.org/wiki/Greeks_(finance))”).
  - Delta: the rate of change of the theoretical option value with respect to changes in the underlying asset's price
  - Vega: sensitivity to volatility
  - Theta: sensitivity of the value of the derivative to the passage of time
  - Rho: sensitivity to the interest rate
- Simulated correlated Equities using [Cholesky Decomposition](https://en.wikipedia.org/wiki/Cholesky_decomposition).
  -  Cholesky Decomposition is used to generate correlated random variables (e.g. modeling products whose price/payoff is dependent on multiple assets).
     - correlation matrix P can be decomposed as P = L • L
     - X is uncorrelated random variable vector
     - correlated random variable vector Z can be generated as Z = L • X
