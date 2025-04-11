#include "./random.hpp"
#include <algorithm>
#include <chrono>
#include <corecrt_math_defines.h>
#include <random>


int Random::random_binary() {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 generator(seed);
  std::uniform_int_distribution<int> uniformIntDistribution(0, 1);
  return uniformIntDistribution(generator);
}

int Random::random_int(int min, int max) {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 generator(seed);
  std::uniform_int_distribution<int> uniformIntDistribution(min, max);
  return uniformIntDistribution(generator);
}

double Random::random_double(int min, int max) {
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  std::mt19937 generator(seed);
  std::uniform_real_distribution<double> uniformRealDistribution(min, max);
  return uniformRealDistribution(generator);
}

int Random::geometric_law() {
  int value = Random::random_int(0, 10);
  int round = 1;
  while (value != 10) {
    value = Random::random_int(0, 10);
    round++;
  }
  return round;
}

double Random::cauchy_law(double m, double gamma) {

  double u = Random::random_double(0, 1);

  return m + gamma * tan(M_PI * (u - 0.5));
}

float Random::gaussian_law(float mean, float stddev) {
  double u1 = Random::random_double(0, 1);
  double u2 = Random::random_double(0, 1);

  u1 = std::max(u1, 1e-6);

  double z0 = std::sqrt(-2.0 * std::log(u1)) * std::cos(2 * M_PI * u2);
  double value = mean + z0 * stddev;

  value = std::max<double>(value, -0.1f);
  value = std::min<double>(value, 0.1f);

  return static_cast<float>(value);
}

int Random::exponential_law(double lambda) {
  double u = Random::random_double(0, 1);
  while (u <= 0.0) {
    u = Random::random_double(0, 1);
  }

  double result = -std::log(u) / lambda;
  return static_cast<int>(result);
}

bool Random::bernoulli_law(double p) {
  double u = Random::random_double(0, 1);
  return u < p;
}

double Random::poisson_law(int lambda, int k) {
  double lambda_k = std::pow(lambda, k);
  double exp_neg_lambda = std::exp(-lambda);

  double factorial_k = 1.0;
  for (int i = 1; i <= k; ++i) {
    factorial_k *= i;
  }
  double probability = (lambda_k * exp_neg_lambda) / factorial_k;
  return probability;
}

double Random::pareto_law(double alpha, double x_m) {
  double u = Random::random_double(0.0, 1.0);

  double result = x_m * std::pow(1.0 / u, 1.0 / alpha);
  return result;
}