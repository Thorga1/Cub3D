# cub3D

A first-person 3D maze explorer written in C, built as part of the **42 school** curriculum. Inspired by *Wolfenstein 3D*, cub3D uses raycasting to turn a 2D map into a textured 3D view you can walk around in, rendered with the MiniLibX graphics library.

The program reads a `.cub` scene file describing wall textures, floor and ceiling colors, and the map layout, validates it, and then drops you into the maze.

---

## Features

**Rendering**
- Raycasting engine that casts one ray per screen column
- Wall hits found by stepping through horizontal and vertical grid intersections, keeping the nearest one
- Fisheye correction so walls stay straight instead of bulging
- Different textures for north, south, east and west facing walls
- Solid floor and ceiling colors defined in the scene file
- 960x720 window with a 60° field of view

**Movement**
- Walk forward, backward and strafe left/right
- Rotate the camera left and right
- Wall collision, so you can't walk through walls

**Parsing & validation**
- Checks the `.cub` extension and argument count
- Detects missing, duplicated or invalid identifiers
- Validates texture paths and RGB values (each in `0-255`)
- Ensures exactly one player spawn point
- Flood fill check to make sure the map is fully enclosed by walls
- Handles irregular map shapes and spaces inside the map

---

## Installation

### Requirements
- Linux with X11
- `cc` / `gcc` and `make`
- X11 development libraries and zlib
- [MiniLibX for Linux](https://github.com/42Paris/minilibx-linux)

On Debian/Ubuntu:
```bash
sudo apt install build-essential libx11-dev libxext-dev zlib1g-dev
```

### Build
MiniLibX isn't included in the repository, so clone it into `mlx_linux` first:

```bash
git clone https://github.com/Thorga1/Cub3d.git
cd Cub3d
git clone https://github.com/42Paris/minilibx-linux.git mlx_linux
make
```

### Run
```bash
./cub3D maps/map1.cub
```

### Make targets
| Target | Description |
|--------|-------------|
| `make` / `make all` | Builds MiniLibX and `cub3D` |
| `make clean` | Removes object files |
| `make fclean` | Removes object files and the binary |
| `make re` | Full rebuild |

---

## Controls

| Key | Action |
|-----|--------|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `←` | Rotate left |
| `→` | Rotate right |
| `Esc` | Quit |

Closing the window with the red cross also quits cleanly.

---

## The `.cub` file format

A scene file contains six identifiers followed by the map. Identifiers can appear in any order and can be separated by empty lines; the map must come last.

```
NO north.xpm
SO south.xpm
WE west.xpm
EA east.xpm

F 15,6,40
C 35,19,73

111111111111111
111111000111111
111110000011111
1111000N0001111
111000000000111
110000000000011
100001111100001
111111111111111
```

| Identifier | Meaning |
|------------|---------|
| `NO` | Path to the north wall texture (`.xpm`) |
| `SO` | Path to the south wall texture |
| `WE` | Path to the west wall texture |
| `EA` | Path to the east wall texture |
| `F`  | Floor color as `R,G,B` |
| `C`  | Ceiling color as `R,G,B` |

Map characters:

| Char | Meaning |
|------|---------|
| `1` | Wall |
| `0` | Empty floor |
| `N` `S` `E` `W` | Player spawn, facing that direction |
| ` ` (space) | Void, must not touch walkable space |

The map must be closed: every walkable cell has to be surrounded by walls. If the file is invalid, the program prints `Error` followed by an explanation and exits.

Sample maps live in the `maps/` folder.

---

## Project structure

```
Cub3d/
├── includes/
│   └── cub3d.h           # Structs, constants, prototypes
├── maps/                 # Sample .cub scenes
├── srcs/
│   ├── main.c            # Entry point, hooks and main loop
│   ├── parsing/          # .cub reading, identifiers, colors, textures, flood fill
│   ├── draw/             # Raycasting, wall strips, textures, fisheye fix
│   ├── mlx_play/         # Window setup, key handling, movement, cleanup
│   └── utils/            # String helpers, math helpers
├── north.xpm             # Wall textures
├── south.xpm
├── east.xpm
├── west.xpm
└── Makefile
```

### How a frame is drawn

1. **Background**: the top half of the image is filled with the ceiling color, the bottom half with the floor color.
2. **Cast rays**: for every column of the screen, a ray is cast from the player across the field of view.
3. **Find the wall**: the ray steps through horizontal and vertical grid lines until it hits a wall, and the closest hit is kept.
4. **Fix distortion**: the distance is corrected relative to the player's facing direction to remove the fisheye effect.
5. **Draw the strip**: the wall height is computed from that distance, and the right column of the matching texture is scaled onto the screen.
6. **Display**: the finished image is pushed to the window.

---

## Authors

- **Thorgal Ordner** ([@Thorga1](https://github.com/Thorga1)), `tordner` @ 42
- **Yurong Wang**, `yurwang` @ 42
