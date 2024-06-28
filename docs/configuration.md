# Setting up the JSON configuration file

This document explains how to set up the `config.json` file for the game. The
JSON file is used to set parameters that affect the behaviour and appearance of
the game.

The configuration file sets the screen dimensions and frame rate at the start of
the game. `LoadConfig` reads `config.json` and uses the values for maxfps, width and
height to configure the game environment.

If the `config.json` file can't be found or opened, the program will display an
error. Make sure the config.json file is in the right place with the right
fields for the game to work.

## Fields

|Field|Description|Type|Example|
|---|---|---|---|
|`maxfps`|Specifies the maximum frames per second (FPS) the game should attempt to run at.|Integer|`60`|
|`width`|Specifies the width of the game screen in pixels.|Integer|`800`|
|`height`|Specifies the height of the game screen in pixels.|Integer|`600`|

### Example

```json
{
  "maxfps": 60,
  "width": 800,
  "height": 600
}
```

### Explanation

  - `maxfps`: This field sets the maximum FPS to 60. The game will run at a
    frame rate that is 75% of this value, i.e., 45 FPS.
  - `width`: This field sets the width of the game screen to 800 pixels.
  - `height`: This field sets the height of the game screen to 600 pixels.

*The documentation for this program is licensed under the [GNU Free Documentation Licence 1.3](LICENSE.md), unless stated otherwise.*
