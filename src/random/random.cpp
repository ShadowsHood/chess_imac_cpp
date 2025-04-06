#include "./random.hpp"
#include "random/random.hpp"
#include <chrono>
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

int Random::geometric_law_int() {
  int value {};
  int round {0};
  do {
    value = Random::random_int(0, 10);
    round ++;
  } while (value != 10);
  return round;
}