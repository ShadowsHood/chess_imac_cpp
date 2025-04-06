#pragma once

namespace Random {
int random_binary();

int random_int(int min, int max);
double random_double(int min, int max);
int geometric_law_int();
double cauchy_law_double(double m, double gamma);

} // namespace Random