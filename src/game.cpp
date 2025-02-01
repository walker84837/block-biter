#include "game.h"
#include "err_handling.h"
#include <iostream>
#include <random>
#include <nlohmann/json.hpp>
#include <fstream>

Game::Game() {
  for (int i = 0; i < GRID_WIDTH; ++i) {
    for (int j = 0; j < GRID_HEIGHT; ++j) {
      grid_[i][j] = Block::kEmpty;
    }
  }
}

int LoadConfig(int &frame_rate, int &screen_width, int &screen_height) {
  std::ifstream config("config.json");
  if (!config.is_open()) {
    return error("File \"config.json\" doesn't exist.", 1);
  }

  nlohmann::json data;
  config >> data;

  int fps_max = static_cast<int>(data["maxfps"]) - 1;
  frame_rate = static_cast<int>(fps_max * 0.75);
  screen_width = static_cast<int>(data["width"]);
  screen_height = static_cast<int>(data["height"]);
  return 0;
}

void Game::Run() {
  if (LoadConfig(frame_rate_, screen_width_, screen_height_) != 0) std::exit(1);
  
  InitWindow(screen_width_, screen_height_, "Block Biter");
  SetTargetFPS(frame_rate_);

  alive_ = true;
  running_ = true;
  ReplaceFood();
  GameLoop();
}

void Game::ReplaceFood() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<int> x_dist(0, GRID_WIDTH - 1);
  std::uniform_int_distribution<int> y_dist(0, GRID_HEIGHT - 1);

  while (true) {
    int x = x_dist(gen);
    int y = y_dist(gen);

    if (grid_[x][y] == Block::kEmpty) {
      grid_[x][y] = Block::kFood;
      food_ = {static_cast<float>(x), static_cast<float>(y)};
      break;
    }
  }
}

void Game::GameLoop() {
  while (running_) {
    PollEvents();
    Update();
    Render();
  }
  CloseWindow();
}

void Game::PollEvents() {
  if (WindowShouldClose()) {
    running_ = false;
  }

  if (IsKeyPressed(KEY_UP) && last_dir_ != Move::kDown) dir_ = Move::kUp;
  if (IsKeyPressed(KEY_DOWN) && last_dir_ != Move::kUp) dir_ = Move::kDown;
  if (IsKeyPressed(KEY_LEFT) && last_dir_ != Move::kRight) dir_ = Move::kLeft;
  if (IsKeyPressed(KEY_RIGHT) && last_dir_ != Move::kLeft) dir_ = Move::kRight;

  if (IsKeyPressed(KEY_ESCAPE) || IsKeyPressed(KEY_Q)) {
    running_ = false;
  }
}

void Game::EndGame() {
  std::cout << "Game Over!" << std::endl << "Score: " << score_ << std::endl;
  std::exit(0);
}

void Game::GrowBody(int quantity) {
  growing_ += quantity;
}

void Game::Update() {
  if (!alive_) {
    EndGame();
  }

  switch (dir_) {
    case Move::kUp:
      pos_.y -= speed_;
      break;
    case Move::kDown:
      pos_.y += speed_;
      break;
    case Move::kLeft:
      pos_.x -= speed_;
      break;
    case Move::kRight:
      pos_.x += speed_;
      break;
  }

  if (pos_.x < 0) pos_.x = GRID_WIDTH - 1;
  if (pos_.x > GRID_WIDTH - 1) pos_.x = 0;
  if (pos_.y < 0) pos_.y = GRID_HEIGHT - 1;
  if (pos_.y > GRID_HEIGHT - 1) pos_.y = 0;

  int new_x = static_cast<int>(pos_.x);
  int new_y = static_cast<int>(pos_.y);
  if (new_x != head_.x || new_y != head_.y) {
    last_dir_ = dir_;

    if (growing_ > 0) {
      size_++;
      body_.push_back(head_);
      growing_--;
      grid_[static_cast<int>(head_.x)][static_cast<int>(head_.y)] = Block::kBody;
    } else {
      Vector2 free = head_;
      for (auto it = body_.rbegin(); it != body_.rend(); ++it) {
        grid_[static_cast<int>(free.x)][static_cast<int>(free.y)] = Block::kBody;
        std::swap(*it, free);
      }
      grid_[static_cast<int>(free.x)][static_cast<int>(free.y)] = Block::kEmpty;
    }
  }

  head_.x = new_x;
  head_.y = new_y;

  Block &next = grid_[static_cast<int>(head_.x)][static_cast<int>(head_.y)];
  if (next == Block::kFood) {
    score_++;
    ReplaceFood();
    GrowBody(1);
  } else if (next == Block::kBody) {
    alive_ = false;
  }

  next = Block::kHead;
}

void Game::Render() {
  BeginDrawing();
  ClearBackground(BACKGROUND_COLOR);

  int block_width = screen_width_ / GRID_WIDTH;
  int block_height = screen_height_ / GRID_HEIGHT;

  // Render food
  DrawRectangle(food_.x * block_width, food_.y * block_height, block_width, block_height, FOOD_COLOR);

  // Render snake's body
  for (const auto &point : body_) {
    DrawRectangle(point.x * block_width, point.y * block_height, block_width, block_height, SNAKE_BODY_COLOR);
  }

  // Render snake's head
  Color head_color = alive_ ? SNAKE_HEAD_COLOR : SNAKE_DEAD_COLOR;
  DrawRectangle(head_.x * block_width, head_.y * block_height, block_width, block_height, head_color);

  EndDrawing();
}
