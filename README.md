# 🎮 cub3D - My First RayCaster

<div align="center">

![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
![42](https://img.shields.io/badge/42-000000?style=for-the-badge&logo=42&logoColor=white)
![Status](https://img.shields.io/badge/status-completed-success?style=for-the-badge)

**A 3D maze game inspired by Wolfenstein 3D, built from scratch using raycasting**

[Features](#-features) • [Installation](#️-installation) • [Usage](#-usage) • [Controls](#-controls) • [Technical Details](#-technical-details)

![cub3D Demo](https://via.placeholder.com/800x400/1a1a1a/ffffff?text=cub3D+Game+Screenshot)

</div>

---

## 📖 About The Project

**cub3D** is a 42 school project that recreates the raycasting engine that powered legendary games like **Wolfenstein 3D** (1992). This project demonstrates the fundamentals of 3D graphics rendering, game development, and real-time optimization—all implemented in C using the MLX42 graphics library.

### What is Raycasting?

Raycasting is a rendering technique that creates a 3D perspective from a 2D map by:
1. Casting rays from the player's viewpoint
2. Calculating the distance to walls
3. Rendering vertical strips based on distance (creating depth perception)

This technique was revolutionary in early FPS games and remains an elegant solution for pseudo-3D rendering.

---

## ✨ Features

### Mandatory
- ✅ **Full 3D Raycasting Engine** - Real-time first-person perspective rendering
- ✅ **Textured Walls** - Different textures for North, South, East, and West walls
- ✅ **Smooth Movement** - WASD movement with arrow key rotation
- ✅ **Custom Maps** - Parse and validate `.cub` configuration files
- ✅ **Floor & Ceiling Colors** - Configurable RGB colors
- ✅ **Collision Detection** - Realistic wall collision physics

### Bonus
- 🎯 **Mouse Rotation** - FPS-style mouse look controls
- 🗺️ **Dynamic Minimap** - Real-time overhead view that follows the player
- 🔫 **Animated Weapon** - Doom-style shotgun with shooting animation
- 🚪 **Interactive Doors** - Open and close doors with 'E' key
- 🎨 **Enhanced Graphics** - Optimized rendering with smooth frame rates

---

## 🛠️ Installation

### Prerequisites

```bash
# Linux
sudo apt-get update
sudo apt-get install build-essential libx11-dev libglfw3-dev libglfw3 xorg-dev

# macOS
brew install glfw cmake
```

### Building the Project

```bash
# Clone the repository
git clone https://github.com/ssbaytri/Cub3D.git
cd Cub3D/cub3D

# Compile
make

# Compile with bonus features
make bonus

# Clean build files
make clean    # Remove object files
make fclean   # Remove object files and executable
make re       # Rebuild everything
```

---

## 🎮 Usage

### Running the Game

```bash
./cub3D map.cub
```

### Map File Format

Create a `.cub` file with the following structure:

```
NO ./textures/north_wall.png
SO ./textures/south_wall.png
WE ./textures/west_wall.png
EA ./textures/east_wall.png

F 220,100,0
C 225,30,0

1111111111111111111111111
1000000000110000000000001
1011000001110000000000001
1001000000000000000000001
111111111011000001110000000000001
100000000011000001110111111111111
11110111111111011100000010001
11110111111111011101010010001
11000000110101011100000010001
10000000000000001100000010001
10000000000000001101010010001
11000001110101011111011110N0111
11110111 1110101 101111010001
11111111 1111111 111111111111
```

**Map Legend:**
- `0` = Empty space (floor)
- `1` = Wall
- `D` = Door (bonus)
- `N/S/E/W` = Player starting position and orientation
- `F` = Floor RGB color (0-255)
- `C` = Ceiling RGB color (0-255)

---

## 🕹️ Controls

### Movement
| Key | Action |
|-----|--------|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |

### Camera
| Input | Action |
|-------|--------|
| `←` | Rotate camera left |
| `→` | Rotate camera right |
| `Mouse` | Look around (bonus) |

### Interaction
| Key | Action |
|-----|--------|
| `E` | Open/Close door (bonus) |
| `Left Click` | Shoot weapon (bonus) |
| `ESC` | Exit game |

---

## 🔧 Technical Details

### Architecture

```
cub3D/
├── main/                 # Main game loop and initialization
├── parsing/              # Map and config file parsing
├── raycasting/           # Core raycasting engine
│   ├── Wall rendering
│   ├── Texture mapping
│   ├── Player movement
│   ├── Minimap (bonus)
│   ├── Doors (bonus)
│   └── Animations (bonus)
├── textures/             # Game textures (PNG files)
├── libft/                # Custom C library
├── mlx/                  # MLX42 graphics library (macOS)
├── mlx_linux/            # MLX42 graphics library (Linux)
├── cub.h                 # Main header file
├── map.cub               # Example map file
└── Makefile              # Build configuration
```

### Key Algorithms

#### 1. **DDA Raycasting Algorithm**
```
For each vertical screen strip:
  1. Cast a ray from player position
  2. Check horizontal grid intersections
  3. Check vertical grid intersections
  4. Choose closest intersection
  5. Calculate wall height based on distance
  6. Render textured wall strip
```

#### 2. **Fisheye Correction**
```c
corrected_distance = actual_distance * cos(ray_angle - player_angle)
```
Prevents the "fisheye" distortion effect by using perpendicular distance instead of Euclidean distance.

#### 3. **Texture Mapping**
```c
texture_x = (wall_hit_position % TILE_SIZE) / TILE_SIZE * texture_width
texture_y = (pixel_y / wall_height) * texture_height
```
Maps 2D texture coordinates onto 3D wall surfaces.

### Performance Optimizations

- ✅ **Tile-based minimap rendering** - Only renders visible tiles
- ✅ **Early ray termination** - Stops raycasting when wall is hit
- ✅ **Integer-based scaling** - Fast texture scaling for sprites
- ✅ **Efficient memory management** - Minimal allocations per frame
- ✅ **Normalized angle caching** - Prevents redundant calculations

---

## 🎨 Graphics Techniques

### Wall Rendering
- **Distance-based height calculation** using projection plane
- **Texture mapping** with proper U/V coordinates
- **Different textures** based on wall orientation (N/S/E/W)
- **Smooth transitions** between textures

### Sprite System (Bonus)
- **2D sprite overlay** for weapon
- **Frame-based animation** with configurable timing
- **Transparency support** with alpha channel
- **Scaled rendering** for different sprite sizes

### Minimap (Bonus)
- **Real-time world-to-screen transformation**
- **Smooth scrolling** without jitter
- **Color-coded elements** (walls, floors, doors, player)
- **Direction indicator** showing player orientation

---

## 🚀 Challenges & Solutions

### Challenge 1: Texture Distortion Near Walls
**Problem:** Textures appeared stretched when very close to walls.

**Solution:** Implemented unclamped coordinate system for texture mapping:
```c
int distance_from_top = screen_y - wall_top_unclamped;
int texture_y = (distance_from_top / wall_height) * texture_height;
```

### Challenge 2: Minimap Jittering
**Problem:** Minimap tiles jumped around during movement.

**Solution:** Used sub-pixel offset correction:
```c
int pixel_offset_x = (int)((player_x % TILE_SIZE) / scale);
screen_x = base_x - pixel_offset_x;
```

### Challenge 3: Ray Precision at Grid Boundaries
**Problem:** Rays sometimes missed walls at tile boundaries.

**Solution:** Used epsilon offset for boundary checks:
```c
#define EPSILON 0.0001
y_intersection = tile_boundary - EPSILON;
```

---

## 📚 Resources

### Raycasting Theory
- [Lode's Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html)
- [Permadi's Ray-Casting Tutorial](https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents/)
- [Wolfenstein 3D Source Code](https://github.com/id-Software/wolf3d)

### Mathematics
- Trigonometry (sin, cos, tan)
- Vector mathematics
- 2D rotation matrices
- Distance calculations (Euclidean, Manhattan)

### Graphics Programming
- Texture mapping
- Sprite rendering
- Color manipulation (RGBA)
- Alpha blending

---

## 🐛 Known Issues

- None currently! 🎉

---

## 🤝 Contributing

This is a school project and is not open for contributions. However, feel free to fork and experiment!

---

## 📝 License

This project is part of the 42 school curriculum. All rights reserved.

---

## 👨‍💻 Author

**ssbaytri**
- 42 Intra: `ssbaytri`
- GitHub: [@ssbaytri](https://github.com/ssbaytri)

---

## 🙏 Acknowledgments

- **42 Network** for the amazing project
- **Id Software** for creating Wolfenstein 3D and inspiring generations of game developers
- **John Carmack** for pioneering raycasting techniques
- **MLX42** developers for the graphics library
- All the peers who helped during development and evaluation

---

<div align="center">

**Made with ❤️ and lots of ☕ at 42**

⭐ Star this repo if you found it helpful!

</div>
