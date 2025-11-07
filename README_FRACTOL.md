# Fractol - École 42 Project

A fractal viewer implementing the **Model-View-Controller (MVC)** architecture pattern using the MiniLibX graphics library for Ubuntu.

## About

Fractol is a project from École 42 that explores the world of fractals. This implementation displays beautiful mathematical fractals like the Mandelbrot and Julia sets with an interactive interface allowing zoom and navigation.

## Architecture

This project follows the **MVC (Model-View-Controller)** design pattern:

### Model (`src/model/`)
- **fractal_calc.c**: Mathematical calculations for fractals
  - Mandelbrot set algorithm
  - Julia set algorithm
  - Complex number operations
  - Color mapping functions

### View (`src/view/`)
- **render.c**: Graphics and rendering logic
  - MLX window initialization
  - Image buffer management
  - Pixel rendering
  - Display updates

### Controller (`src/controller/`)
- **events.c**: User input and event handling
  - Keyboard controls
  - Mouse controls
  - Zoom and pan logic
  - Application state management

## Features

- ✨ **Mandelbrot Set**: Classic fractal with infinite detail
- 🎨 **Julia Set**: Beautiful fractal patterns
- 🔍 **Zoom**: Explore fractals at different scales
- 🎮 **Interactive Controls**: Keyboard and mouse navigation
- 🌈 **Smooth Colors**: Beautiful gradient color schemes
- 🏗️ **MVC Architecture**: Clean, maintainable code structure

## Requirements

- GCC compiler
- Make
- X11 development libraries
- Git (for downloading MiniLibX)

### Installing Dependencies (Ubuntu/Debian)

```bash
sudo apt-get update
sudo apt-get install build-essential libx11-dev libxext-dev libbsd-dev
```

## Installation

1. Clone the repository:
```bash
git clone https://github.com/marzelion/skills-introduction-to-github.git
cd skills-introduction-to-github
```

2. Build the project:
```bash
make
```

The Makefile will automatically download and compile the MiniLibX library.

## Usage

Run the program with a fractal type:

```bash
./fractol mandelbrot
```

or

```bash
./fractol julia
```

### Controls

| Key/Action | Function |
|------------|----------|
| **ESC** | Exit program |
| **Arrow Keys** | Move view (pan) |
| **+** | Zoom in |
| **-** | Zoom out |
| **Mouse Wheel** | Zoom in/out |

## Project Structure

```
fractol/
├── includes/
│   └── fractol.h          # Main header file with structures and prototypes
├── src/
│   ├── main.c             # Entry point and program initialization
│   ├── model/
│   │   └── fractal_calc.c # Fractal mathematics (Model)
│   ├── view/
│   │   └── render.c       # Graphics and rendering (View)
│   └── controller/
│       └── events.c       # Event handling and logic (Controller)
├── Makefile               # Build configuration
└── README_FRACTOL.md      # This file
```

## MVC Architecture Explanation

### Model Layer
The Model layer contains all the mathematical logic and data structures for fractal calculations. It's independent of the display and user interface.

**Responsibilities:**
- Calculate iteration counts for Mandelbrot and Julia sets
- Convert screen coordinates to complex plane coordinates
- Generate color values based on iteration counts
- Store fractal parameters (zoom, position, type)

### View Layer
The View layer handles all graphics operations and rendering. It interacts with MiniLibX to display the fractals.

**Responsibilities:**
- Initialize MLX windows and images
- Render pixels to the screen
- Update the display
- Manage graphics resources

### Controller Layer
The Controller layer manages user input and coordinates between Model and View. It updates the Model based on user actions and triggers View updates.

**Responsibilities:**
- Handle keyboard events
- Handle mouse events
- Manage zoom and pan operations
- Coordinate re-rendering when parameters change

## Building

```bash
# Build the project
make

# Clean object files
make clean

# Clean everything including binary
make fclean

# Rebuild from scratch
make re

# Clean only MLX
make mlx_clean

# Remove MLX completely
make mlx_fclean
```

## Examples

### Mandelbrot Set
The Mandelbrot set is defined by the iteration of the complex quadratic polynomial:
```
z(n+1) = z(n)² + c
```
where `z(0) = 0` and `c` is the complex number corresponding to the pixel position.

### Julia Set
The Julia set uses the same formula but with a fixed constant `c` and varying starting points `z(0)`:
```
z(n+1) = z(n)² + c
```
where `z(0)` varies with pixel position and `c` is a constant (default: -0.7 + 0.27015i).

## Technical Details

- **Window Size**: 800x600 pixels
- **Maximum Iterations**: 100 (adjustable in fractol.h)
- **Color Mapping**: Smooth gradient based on iteration count
- **Zoom**: Multiplicative scaling with keyboard/mouse
- **Pan**: Additive offset with arrow keys

## Credits

- École 42 for the project specification
- MiniLibX graphics library
- Mathematical foundations from Benoît Mandelbrot and Gaston Julia

## License

This project is part of the École 42 curriculum.
