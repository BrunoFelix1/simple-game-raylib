# Monster Survival Game

A survival game developed in **C** using the **Raylib** graphics library. The objective is to escape from ghosts for as long as possible while controlling a gunslinger in the Old West.

## Project Overview

This project was developed to enhance knowledge in:
- C programming
- Raylib game development library
- Vector manipulation and game mathematics
- Collision detection and management
- Structure-oriented programming

## How to Play

- **Arrow keys**: Move the player
- **P**: Pause/Unpause the game
- **Enter**: Restart after game over

### Objective
Survive as long as possible by avoiding being caught by the red ghosts that chase you!

## Technologies Used

- **Language**: C
- **Graphics Library**: Raylib
- **IDE**: Visual Studio Code
- **Compiler**: GCC

## Features

### Implemented
- Smooth player movement
- Intelligent enemy pursuit system
- Collision detection between player and monsters
- Monster-to-monster collision system (prevents overlapping)
- Thematic Old West background music
- Pause system
- Survival time counter
- Custom sprites (gunslinger, ghosts, scenery)
- Game over screen with restart option

### Visual Assets
- Gunslinger sprite (gunslinger.png)
- Ghost sprites (fantasma.png)
- Old West scenery (teladefundo.png)
- Ambient music (OldWest.mp3)

## Code Structure

### Main Structures
```c
typedef struct Player {
    Vector2 position;
    Vector2 size;
    float speed;
    Rectangle rectangle_player;
    Color color;
} Player;

typedef struct Monster {
    Vector2 position;
    float speed;
    float radius;
    bool active;
    Color color;
} Monster;
```

### Custom Mathematical Functions
- `MyVector2Subtract()`: Vector subtraction
- `MyVector2Normalize()`: Vector normalization
- `MyVector2Distance()`: Distance calculation between vectors

## How to Run

### Prerequisites
- Raylib library installed
- GCC compiler
- Windows/Linux/macOS system

### Compilation
```bash
gcc SurvivalSimples.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o game
```

### Execution
```bash
./game
```

## Project Structure

```
simple-game-raylib/
├── SurvivalSimples.c          # Main game code
├── README.md                  # Project documentation
└── resources/                 # Game assets
    ├── fantasma.png          # Monster sprites
    ├── gunslinger.png        # Player sprite
    ├── OldWest.mp3          # Background music
    └── teladefundo.png      # Background image
```

## Game Mechanics

### Pursuit System
The ghosts use a vector-based pursuit algorithm, constantly moving towards the player using normalized vectors.

### Anti-Overlap Collision System
Implementation of logic to prevent monsters from overlapping, creating more fluid and visually appealing gameplay.

### Boundary Control
The player is constrained to the screen edges, preventing movement outside the visual game limits.

## Technical Specifications

- **Language**: C (100%)
- **Target FPS**: 60 FPS
- **Resolution**: 1080x720
- **Maximum Monsters**: 4 simultaneous
- **Monster Speed**: 1.5 units/frame

## Learning Outcomes and Achievements

- Implementation of vector mathematics in games
- Game state management (playing, paused, game over)
- Real-time collision optimization
- Audio-visual asset integration
- Modular code architecture in C

## Future Improvements

- Power-up system
- Different enemy types
- Scoring system
- Multiple levels
- Sound effects
- Visual particle effects

## Developer

**Bruno** - Software Developer  
Focused on improving skills in game programming and graphics libraries

---

*Project developed as part of continuous study in game development and C programming.*