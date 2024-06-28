#include <algorithm>
#include <iostream>
#include <string>
#include <thread>
#include "game.h"

void GetExitInput() {
  auto ToLowercase = [](const std::string &input) -> std::string {
    std::string result = input;
    std::transform(result.begin(), result.end(), result.begin(), ::tolower);
    return result;
  };

  std::cout << "Type \"q\", \"exit\" or \"quit\" to quit the game." << '\n';
  std::string input;
  while (true) {
    std::getline(std::cin, input);
    std::string input_lower = ToLowercase(input);
    if (input_lower == "q" || input_lower == "exit" || input_lower == "quit") {
      std::cout << "Exiting..." << '\n';
      std::exit(0);
    }
  }
}

void RunGame() {
  Game game;
  game.Run();
}

int main(void) {
  std::thread game_thread(RunGame);
  std::thread input_thread(GetExitInput);
  game_thread.join();
  input_thread.join();
  return 0;
}
