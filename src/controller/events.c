#include "../includes/fractol.h"

/*
 * Handle keyboard input
 */
int	key_press(int keycode, t_fractol *fractol)
{
	if (keycode == KEY_ESC)
		close_window(fractol);
	else if (keycode == KEY_PLUS)
	{
		fractol->params.zoom *= 1.1;
		render_fractal(fractol);
	}
	else if (keycode == KEY_MINUS)
	{
		fractol->params.zoom /= 1.1;
		render_fractal(fractol);
	}
	else if (keycode == KEY_LEFT)
	{
		fractol->params.move_x -= 20;
		render_fractal(fractol);
	}
	else if (keycode == KEY_RIGHT)
	{
		fractol->params.move_x += 20;
		render_fractal(fractol);
	}
	else if (keycode == KEY_UP)
	{
		fractol->params.move_y -= 20;
		render_fractal(fractol);
	}
	else if (keycode == KEY_DOWN)
	{
		fractol->params.move_y += 20;
		render_fractal(fractol);
	}
	return (0);
}

/*
 * Handle mouse button events (zoom with scroll wheel)
 */
int	mouse_hook(int button, int x, int y, t_fractol *fractol)
{
	double	zoom_factor;

	(void)x;
	(void)y;
	if (button == 4)  /* Scroll up - zoom in */
		zoom_factor = 1.1;
	else if (button == 5)  /* Scroll down - zoom out */
		zoom_factor = 0.9;
	else
		return (0);
	fractol->params.zoom *= zoom_factor;
	render_fractal(fractol);
	return (0);
}

/*
 * Close window and exit program
 */
int	close_window(t_fractol *fractol)
{
	destroy_view(&fractol->view);
	exit(0);
	return (0);
}

/*
 * Initialize fractol structure with default values
 */
void	init_fractol(t_fractol *fractol, int type)
{
	fractol->params.type = type;
	fractol->params.zoom = 1.0;
	fractol->params.move_x = 0.0;
	fractol->params.move_y = 0.0;
	if (type == MANDELBROT)
	{
		fractol->params.min_real = -2.5;
		fractol->params.max_real = 1.0;
		fractol->params.min_imag = -1.2;
		fractol->params.max_imag = 1.2;
	}
	else  /* JULIA */
	{
		fractol->params.min_real = -2.0;
		fractol->params.max_real = 2.0;
		fractol->params.min_imag = -1.5;
		fractol->params.max_imag = 1.5;
		fractol->params.julia_real = -0.7;
		fractol->params.julia_imag = 0.27015;
	}
}
