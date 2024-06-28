#ifndef GAME_H
#define GAME_H

#include <raylib.h>
#include <vector>

constexpr int GRID_WIDTH = 32;
constexpr int GRID_HEIGHT = 32;

class Game {
 public:
  Game();
  void Run();

 private:
  enum class Block { kHead, kBody, kFood, kEmpty };
  enum class Move { kUp, kDown, kLeft, kRight };

  struct Position {
    float x = GRID_WIDTH / 2, y = GRID_HEIGHT / 2;
  } pos_;

  Vector2 head_ = {pos_.x, pos_.y};
  Vector2 food_;
  std::vector<Vector2> body_;

  Block grid_[GRID_WIDTH][GRID_HEIGHT];

  bool running_ = false;
  bool alive_ = false;
  Move last_dir_ = Move::kUp;
  Move dir_ = Move::kUp;

  int frame_rate_;
  int screen_width_;
  int screen_height_;
  int growing_ = 0;
  int score_ = 0;
  int size_ = 1;
  float speed_ = 0.5f;

  void EndGame();
  void ReplaceFood();
  void GrowBody(int quantity);
  void GameLoop();
  void Render();
  void Update();
  void PollEvents();
};

#endif  // GAME_H
