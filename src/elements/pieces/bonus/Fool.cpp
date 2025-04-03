#include "./Fool.hpp"
#include "../../../random/random.hpp"
#include "../../Board.hpp"

std::vector<int> Fool::get_possible_moves(const Board &board, int /*position*/) {
  std::vector<int> possible_moves;
  bool empty{};
  bool color{};
  for (int i = 0; i < 64; i++) {
    if (!board.is_empty(i) && board.is_other_color(i, this->get_color())) {
      possible_moves.push_back(i);
    }
  }
  return possible_moves;
}

bool Fool::canMove() {
  double randomValue = Random::random_double(0.0, 1.0);
  double successProbability{};

  if (markovChain == 9) {
    successProbability = 1.0;
  } else {
    successProbability = (1.0 / 10.0) + (markovChain / 100.0);
  }

  if (randomValue < successProbability) {
    markovChain = 0;
    return true;
  } else {
    markovChain = std::min(9, markovChain + 1);
    return false;
  }
}