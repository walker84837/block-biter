# Block Biter

![License](https://img.shields.io/badge/license-GPLv3-blue.svg)

Block Biter is just a fancy nickname to Snake. I built with C++ using Raylib for rendering.

If you live under a rock, you have to guide a snake around a grid, consuming food to grow longer while avoiding hitting with the snake's own body.

## Features

- Configurable settings for frame rate, screen width, and screen height via a simple header file (config.def.h) and a JSON file (config.json).
- It's a snake game, you get the drill.

## Installation

### Prerequisites

- C++17 or later
- Raylib library
- nlohmann/json library
- build tools: [meson](https://mesonbuild.com/), [ninja](https://ninja-build.org/)

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
   $ mkdir build
   $ meson setup build
   $ meson compile -C build
   ```
4. Run the game:
   ``` console
   $ ./build/blockbiter
   ```

## Usage

- Use the arrow keys to control the direction of the snake.
- Avoid colliding with the snake's body or the walls to keep playing.
- Collect food to grow the snake and increase your score.
- To exit the game, type `q`, `exit`, or `quit` in the console.

## Configuration

The game settings are managed via a `config.json` file. Example:
```json
{
  "maxfps": 60,
  "width": 800,
  "height": 600
}
```
Adjust the `maxfps`, `width`, and `height` values to fit your preferences.

Otherwise, the aesthetics (such as colors) are managed via the [config.def.h](src/config.def.h) file.

## Support

For any issues or questions, please open an issue on the GitHub repository.

## Roadmap

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

Currently under occasional development. Contributions and suggestions are highly appreciated.
