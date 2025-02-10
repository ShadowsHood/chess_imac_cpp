#include "./utils.hpp"

void get_step_from_direction(const Direction &direction, int &stepX,
                             int &stepY) {
  switch (direction) {
  case Direction::Up:
    stepX = 0;
    stepY = 1;
    break;
  case Direction::Down:
    stepX = 0;
    stepY = -1;
    break;
  case Direction::Left:
    stepX = -1;
    stepY = 0;
    break;
  case Direction::Right:
    stepX = 1;
    stepY = 0;
    break;
  case Direction::UpLeft:
    stepX = -1;
    stepY = 1;
    break;
  case Direction::UpRight:
    stepX = 1;
    stepY = 1;
    break;
  case Direction::DownLeft:
    stepX = -1;
    stepY = -1;
    break;
  case Direction::DownRight:
    stepX = 1;
    stepY = -1;
    break;
  }
}

void get_linear_moves(std::vector<int> &moves,
                      const std::array<Piece *, 64> &positions_board,
                      const Direction &direction,
                      const std::pair<int, int> &position, Color color,
                      const bool king) {

  int stepX = 0;
  int stepY = 0;
  get_step_from_direction(direction, stepX, stepY);
  std::pair<int, int> new_position(position.first + stepX,
                                   position.second + stepY);
  int new_position_1D = get_pos_1D(new_position);

  if (new_position.first < 7 && new_position.first > 0 &&
      new_position.second < 7 && new_position.second > 0 &&
      (!positions_board[new_position_1D] ||
       color != positions_board[new_position_1D]->get_color())) {
    {
      moves.push_back(new_position_1D);
      if (!king && !positions_board[new_position_1D]) {
        get_linear_moves(moves, positions_board, direction, new_position,
                         color);
      }
    }
  }
}

void get_up_right_moves(std::vector<int> &moves,
                        const std::array<Piece *, 64> &positions_board,
                        const std::pair<int, int> &position, Color color,
                        const bool king) {
  get_linear_moves(moves, positions_board, Direction::UpRight, position, color,
                   king);
}

void get_up_left_moves(std::vector<int> &moves,
                       const std::array<Piece *, 64> &positions_board,
                       const std::pair<int, int> &position, Color color,
                       const bool king) {
  get_linear_moves(moves, positions_board, Direction::UpLeft, position, color,
                   king);
}

void get_down_right_moves(std::vector<int> &moves,
                          const std::array<Piece *, 64> &positions_board,
                          const std::pair<int, int> &position, Color color,
                          const bool king) {
  get_linear_moves(moves, positions_board, Direction::DownRight, position,
                   color, king);
}

void get_down_left_moves(std::vector<int> &moves,
                         const std::array<Piece *, 64> &positions_board,
                         const std::pair<int, int> &position, Color color,
                         const bool king) {
  get_linear_moves(moves, positions_board, Direction::DownLeft, position, color,
                   king);
}

void get_up_moves(std::vector<int> &moves,
                  const std::array<Piece *, 64> &positions_board,
                  const std::pair<int, int> &position, Color color,
                  const bool king) {
  get_linear_moves(moves, positions_board, Direction::Up, position, color,
                   king);
}

void get_down_moves(std::vector<int> &moves,
                    const std::array<Piece *, 64> &positions_board,
                    const std::pair<int, int> &position, Color color,
                    const bool king) {
  get_linear_moves(moves, positions_board, Direction::Down, position, color,
                   king);
}

void get_right_moves(std::vector<int> &moves,
                     const std::array<Piece *, 64> &positions_board,
                     const std::pair<int, int> &position, Color color,
                     const bool king) {
  get_linear_moves(moves, positions_board, Direction::Right, position, color,
                   king);
}

void get_left_moves(std::vector<int> &moves,
                    const std::array<Piece *, 64> &positions_board,
                    const std::pair<int, int> &position, Color color,
                    const bool king) {
  get_linear_moves(moves, positions_board, Direction::Left, position, color,
                   king);
}