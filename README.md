# Block Biter

![License](https://img.shields.io/badge/license-GPLv3-blue.svg)

Block Biter is an engaging and dynamic take on the classic snake game, built
with C++ and utilizing the Raylib library for rendering. This game challenges
players to navigate a snake around the grid, consuming food to grow longer while
avoiding collisions with the snake's own body.

## Features

- Classic snake gameplay with a modern twist.
- Configurable settings for frame rate, screen width, and screen height via a JSON file.
- Smooth and responsive controls using keyboard inputs.
- Dynamic food placement and snake growth mechanics.

## Installation

### Prerequisites

- C++17 or later
- Raylib library
- nlohmann/json library

### Steps

1. Clone the repository:
   ``` console
   $ git clone https://github.com/walker84837/block-biter.git
   ```
2. Navigate to the project directory:
   ``` console
   $ cd block-biter
   ```
3. Build the project:
   ``` console
   $ make
   ```
4. Run the game:
   ``` console
   $ ./bin/blockbiter
   ```

## Usage

- Use the arrow keys to control the direction of the snake.
- Avoid colliding with the snake's body or the walls to keep playing.
- Collect food to grow the snake and increase your score.
- To exit the game, type `q`, `exit`, or `quit` in the console.

## Configuration

The game configuration is managed via a `config.json` file. Example:
```json
{
  "maxfps": 60,
  "width": 800,
  "height": 600
}
```
Adjust the `maxfps`, `width`, and `height` values to fit your preferences.

## Support

For any issues or questions, please open an issue on the GitHub repository.

## Roadmap

- Add different levels with increasing difficulty.
- Introduce obstacles and power-ups.
- Implement a scoring leaderboard.
- Add sound effects and music.

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request.
For major changes, open an issue first to discuss what you would like to change.

### Getting started

1. Fork the repository.
2. Clone your fork:
   ``` console
   $ git clone https://github.com/walker84837/block-biter.git
   ```
3. Create a new branch:
   ``` console
   $ git checkout -b feature/your-feature
   ```
4. Make your changes and commit them:
   ``` console
   $ git commit -m 'Add some feature'
   ```
5. Push to the branch:
   ``` console
   $ git push origin feature/your-feature
   ```
6. Open a pull request.

## License

This project is licensed under the [GNU GPLv3](LICENSE.md).

## Project Status

Currently under heavy development. Contributions and suggestions are highly appreciated.
