# Fractol MVC Architecture Diagram

```
┌─────────────────────────────────────────────────────────────────────┐
│                         FRACTOL APPLICATION                         │
│                                                                     │
│  ┌─────────────────────────────────────────────────────────────┐  │
│  │                        MAIN (main.c)                         │  │
│  │  • Command-line parsing                                      │  │
│  │  • Application initialization                                │  │
│  │  • MLX event loop coordination                               │  │
│  └────────────────────┬────────────────────────────────────────┘  │
│                       │                                            │
│  ┌────────────────────┴────────────────────────────────────────┐  │
│  │                   CONTROLLER (events.c)                      │  │
│  │  ┌──────────────────────────────────────────────────────┐  │  │
│  │  │  Event Handlers:                                      │  │  │
│  │  │  • key_press()    - Keyboard input (ESC, arrows, +/-) │  │  │
│  │  │  • mouse_hook()   - Mouse scroll zoom                 │  │  │
│  │  │  • close_window() - Clean exit                        │  │  │
│  │  │  • init_fractol() - Initialize parameters             │  │  │
│  │  └──────────────────────────────────────────────────────┘  │  │
│  └───────────┬──────────────────────────────────┬─────────────┘  │
│              │                                   │                 │
│              ↓                                   ↓                 │
│  ┌────────────────────────────┐  ┌───────────────────────────┐   │
│  │  MODEL (fractal_calc.c)    │  │   VIEW (render.c)         │   │
│  │  ┌──────────────────────┐  │  │  ┌────────────────────┐  │   │
│  │  │ Fractal Mathematics   │  │  │  │ Graphics Rendering │  │   │
│  │  │                       │  │  │  │                    │  │   │
│  │  │ • calculate_         │  │  │  │ • init_view()      │  │   │
│  │  │   mandelbrot()       │◀─┼──┼──│ • render_fractal() │  │   │
│  │  │                       │  │  │  │ • put_pixel_to_    │  │   │
│  │  │ • calculate_julia()  │  │  │  │   image()          │  │   │
│  │  │                       │  │  │  │ • destroy_view()   │  │   │
│  │  │ • screen_to_complex()│  │  │  │                    │  │   │
│  │  │                       │  │  │  └────────────────────┘  │   │
│  │  │ • get_fractal_color()│──┼──┼─────────────►              │   │
│  │  │                       │  │  │                           │   │
│  │  └──────────────────────┘  │  │  ┌────────────────────┐  │   │
│  │                             │  │  │   MiniLibX (MLX)   │  │   │
│  │  Data Structures:           │  │  │                    │  │   │
│  │  • t_complex                │  │  │ • mlx_init()       │  │   │
│  │  • t_fractal_params         │  │  │ • mlx_new_window() │  │   │
│  │                             │  │  │ • mlx_new_image()  │  │   │
│  └─────────────────────────────┘  │  │ • mlx_loop()       │  │   │
│                                    │  └────────────────────┘  │   │
│                                    └───────────────────────────┘   │
│                                                                     │
│  ┌─────────────────────────────────────────────────────────────┐  │
│  │                    HEADER (fractol.h)                        │  │
│  │  • Type definitions (t_fractol, t_view, t_fractal_params)    │  │
│  │  • Constants (WIDTH, HEIGHT, ZOOM_FACTOR, etc.)              │  │
│  │  • Function prototypes for all modules                       │  │
│  └─────────────────────────────────────────────────────────────┘  │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘

DATA FLOW:
──────────

1. User Input → CONTROLLER
   ↓
2. CONTROLLER updates fractal parameters
   ↓
3. CONTROLLER calls VIEW to render
   ↓
4. VIEW calls MODEL to calculate each pixel
   ↓
5. MODEL returns color values
   ↓
6. VIEW displays to screen via MLX

KEY FEATURES:
─────────────

✅ Clean separation of concerns (MVC)
✅ Model: Pure mathematical calculations
✅ View: Pure rendering/display logic
✅ Controller: User interaction coordination
✅ No cross-dependencies between layers
✅ Easy to test and maintain
✅ Scalable for adding new fractals
```

## Component Responsibilities

### Model Layer
**Purpose**: Handle all mathematical computations
- Calculate fractal iterations (Mandelbrot, Julia)
- Transform screen coordinates to complex plane
- Generate colors based on iteration counts
- **No dependency on**: View or Controller

### View Layer
**Purpose**: Handle all graphics and rendering
- Initialize MLX windows and images
- Render pixels to screen buffer
- Manage graphics resources
- **Depends on**: Model (for calculations)
- **No dependency on**: Controller

### Controller Layer
**Purpose**: Handle user interaction and coordinate layers
- Process keyboard/mouse events
- Update Model parameters
- Trigger View updates
- Manage application lifecycle
- **Depends on**: Both Model and View

### Benefits of This Architecture
1. **Modularity**: Each component has clear responsibilities
2. **Testability**: Easy to test Model calculations independently
3. **Maintainability**: Changes to one layer don't affect others
4. **Extensibility**: Easy to add new fractals or controls
5. **Reusability**: Model calculations can be reused in different contexts
