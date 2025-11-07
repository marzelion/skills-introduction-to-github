#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "../minilibx-linux/mlx.h"

/* Window dimensions */
# define WIDTH 800
# define HEIGHT 600
# define MAX_ITERATIONS 100

/* Fractal types */
# define MANDELBROT 1
# define JULIA 2

/* Colors */
# define COLOR_BLACK 0x000000
# define COLOR_WHITE 0xFFFFFF
# define COLOR_BLUE 0x0000FF
# define COLOR_GREEN 0x00FF00
# define COLOR_RED 0xFF0000

/* Key codes */
# define KEY_ESC 65307
# define KEY_PLUS 65451
# define KEY_MINUS 65453
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_UP 65362
# define KEY_DOWN 65364

/* Mouse buttons */
# define MOUSE_SCROLL_UP 4
# define MOUSE_SCROLL_DOWN 5

/* Movement and zoom constants */
# define MOVE_STEP 20
# define ZOOM_IN_FACTOR 1.1
# define ZOOM_OUT_FACTOR 0.9

/* Model - Fractal data structure */
typedef struct s_complex
{
	double	real;
	double	imag;
}	t_complex;

typedef struct s_fractal_params
{
	int		type;
	double	min_real;
	double	max_real;
	double	min_imag;
	double	max_imag;
	double	zoom;
	double	move_x;
	double	move_y;
	double	julia_real;
	double	julia_imag;
}	t_fractal_params;

/* View - Graphics and rendering */
typedef struct s_image
{
	void	*img_ptr;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_image;

typedef struct s_view
{
	void	*mlx_ptr;
	void	*win_ptr;
	t_image	img;
}	t_view;

/* Controller - Main application structure */
typedef struct s_fractol
{
	t_view				view;
	t_fractal_params	params;
}	t_fractol;

/* Model functions - Fractal calculations */
int			calculate_mandelbrot(t_complex c);
int			calculate_julia(t_complex z, t_complex c);
t_complex	screen_to_complex(int x, int y, t_fractal_params *params);
int			get_fractal_color(int iterations);

/* View functions - Rendering */
int			init_view(t_view *view);
void		render_fractal(t_fractol *fractol);
void		put_pixel_to_image(t_image *img, int x, int y, int color);
void		destroy_view(t_view *view);

/* Controller functions - Event handling */
int			key_press(int keycode, t_fractol *fractol);
int			mouse_hook(int button, int x, int y, t_fractol *fractol);
int			close_window(t_fractol *fractol);
void		init_fractol(t_fractol *fractol, int type);

/* Utility functions */
void		error_exit(char *message);

#endif
