# Adventure Town 144p (C++ Terminal Game)

A small C++17 text adventure where you choose paths and use elemental attacks (fire / water / earth) to defeat monsters. Built as a first ever solo game project. Cross-platform terminal clear & sleep (ANSI + `std::this_thread::sleep_for`).

## Gameplay
- Pick from the menu: **Start**, **About game**, **About dev**, **Quit**.
- Choose **left** or **right** each level to face a different monster.
- In battle, type an element: `fire`, `water`, or `earth`.
- Element chart:
  - Fire 🔥 beats Earth 🌱  
  - Water 💧 beats Fire 🔥  
  - Earth 🌱 beats Water 💧  
- Ties happen if you match the monster’s element—pick again.
- Final boss selects a random element (no fixed weakness).

## Project Layout
```text
.
├── .gitignore               # local ignore rules (builds, editor files, etc.)
├── adventure_town144p.cpp   # main game source
└── README.md
```

## Build & Run

### macOS / Linux
```bash
g++ -std=c++17 -Wall -Wextra -pedantic -o adventure adventure-town144p/adventure_town144p.cpp
./adventure
```

### Windows (MinGW)
```bash
g++ -std=c++17 -Wall -Wextra -pedantic -o adventure.exe adventure-town144p/adventure_town144p.cpp
.\adventure.exe
```
