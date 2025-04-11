#pragma once

namespace Random {
    
int random_binary();
int random_int(int min, int max);
double random_double(int min, int max);
int geometric_law();
double cauchy_law(double m, double gamma);
float gaussian_law(float mean = 0.0f, float stddev = 0.05f);
int exponential_law(double lambda);
bool bernoulli_law(double p);
double poisson_law(int lambda, int k);
double pareto_law(double alpha, double x_m);

} // namespace Random