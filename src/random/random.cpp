#include "./random.hpp"
#include <chrono>
#include <random>
#include <corecrt_math_defines.h>

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
  int value {};
  int round {0};
  do {
    value = Random::random_int(0, 10);
    round ++;
  } while (value != 10);
  return round;
}

double Random::cauchy_law(double m, double gamma) {
  double u = ((double) rand() / RAND_MAX);
  return m + gamma * tan(M_PI * (u - 0.5));
}

float Random::gaussian_law(float mean, float stddev) {
  double u1 = Random::random_double(0, 1);
  double u2 = Random::random_double(0, 1);

  if (u1 < 1e-6) u1 = 1e-6;

  double z0 = std::sqrt(-2.0 * std::log(u1)) * std::cos(2 * M_PI * u2);
  double value = mean + z0 * stddev;

  if (value < -0.1f) value = -0.1f;
  if (value > 0.1f) value = 0.1f;

  return static_cast<float>(value);
}

int Random::exponential_law(double lambda) {
  double u;
  do {
      u = Random::random_double(0, 1);
  } while (u <= 0.0); 

  double result = -std::log(u) / lambda;
  return static_cast<int>(result); 
}

bool Random::bernoulli_law(double p) {
  double u = Random::random_double(0, 1);
  return u < p;
}