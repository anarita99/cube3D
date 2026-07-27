*This project has been created as part of the 42 curriculum by adores, leramos-.*
 
---
 
# cub3D
 
## Description
 
cub3D is a simple 3D game written in C using the MiniLibX graphics library. Developed as a group project for the 42 school curriculum, it implements a raycasting engine inspired by the classic 1992 game Wolfenstein 3D.
 
The goal of the project is to render a first-person perspective of a maze-like world defined by a 2D grid map. The player can navigate through the environment, with walls rendered in 3D using raycasting. The map is loaded from a `.cub` configuration file that specifies the textures, the grid of the map and floor and ceiling colors.
 
## Instructions
 
### Requirements
 
- Linux / MacOS with X11 support
- `cc` compiler
- `make`
- The `minilibx-linux` folder must be present at the root of the repository — it is not fetched automatically by `make`. Clone it from [42Paris/minilibx-linux](https://github.com/42Paris/minilibx-linux) and place it there before compiling.

### Compilation
 
Clone the repository and compile with:
 
```bash
make
```
 
This will also build the included `libft` and `minilibx-linux` dependencies automatically.
 
### Running
 
```bash
./cub3D maps/map.cub
```
 
Replace `maps/map.cub` with any valid `.cub` map file.
 
### Controls
 
| Key | Action |
|-----|--------|
| `W` `A` `S` `D` | Move forward / left / backward / right |
| `←` `→` | Rotate camera left / right |
| `ESC` | Exit the game |
 
### Cleaning
 
```bash
make clean    # remove object files
make fclean   # remove object files and binary
make re       # full recompile
```
 
### Map format
 
Map files (`.cub`) define wall textures by cardinal direction, floor/ceiling colours, and the 2D grid layout. Example:
 
```
NO ./textures/no.xpm
SO ./textures/so.xpm
WE ./textures/we.xpm
EA ./textures/ea.xpm
 
F 38,48,64
C 135,206,235
 
111111
100001
1000N1
111111
```
 
Grid legend: `1` = wall, `0` = empty space, `N/S/E/W` = player spawn and starting orientation.
 
## Resources
 
### References
 
- [MiniLibX documentation](https://harm-smits.github.io/42docs/libs/minilibx/getting_started.html) — the X-Window graphics library used to handle window creation, input, and rendering
- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) — the main reference for understanding and implementing the raycasting algorithm
- [42 cub3D subject](https://github.com/42Paris/minilibx-linux) — the official project subject defining requirements and constraints

### Textures
 
Wall textures were sourced from:
- [luke100000 – Textures on itch.io](https://luke100000.itch.io/textures)
- [Old School FPS Wall Textures – OpenGameArt](https://opengameart.org/content/old-school-fps-wall-textures)

### AI usage
 
AI was used to help write and format this README file, and to clarify some concepts during development.