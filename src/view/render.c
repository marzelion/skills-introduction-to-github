#include "../includes/fractol.h"

/*
 * Initialize MLX view (window and image)
 */
int	init_view(t_view *view)
{
	view->mlx_ptr = mlx_init();
	if (!view->mlx_ptr)
		return (0);
	view->win_ptr = mlx_new_window(view->mlx_ptr, WIDTH, HEIGHT, "Fractol");
	if (!view->win_ptr)
	{
		mlx_destroy_display(view->mlx_ptr);
		free(view->mlx_ptr);
		return (0);
	}
	view->img.img_ptr = mlx_new_image(view->mlx_ptr, WIDTH, HEIGHT);
	if (!view->img.img_ptr)
	{
		mlx_destroy_window(view->mlx_ptr, view->win_ptr);
		mlx_destroy_display(view->mlx_ptr);
		free(view->mlx_ptr);
		return (0);
	}
	view->img.addr = mlx_get_data_addr(view->img.img_ptr,
			&view->img.bits_per_pixel,
			&view->img.line_length,
			&view->img.endian);
	return (1);
}

/*
 * Put a pixel to the image buffer
 */
void	put_pixel_to_image(t_image *img, int x, int y, int color)
{
	char	*dst;

	if (x >= 0 && x < WIDTH && y >= 0 && y < HEIGHT)
	{
		dst = img->addr + (y * img->line_length + x * (img->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

/*
 * Render the fractal to the screen
 */
void	render_fractal(t_fractol *fractol)
{
	int			x;
	int			y;
	int			iterations;
	int			color;
	t_complex	c;

	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			c = screen_to_complex(x, y, &fractol->params);
			if (fractol->params.type == MANDELBROT)
				iterations = calculate_mandelbrot(c);
			else
			{
				t_complex julia_c;
				julia_c.real = fractol->params.julia_real;
				julia_c.imag = fractol->params.julia_imag;
				iterations = calculate_julia(c, julia_c);
			}
			color = get_fractal_color(iterations);
			put_pixel_to_image(&fractol->view.img, x, y, color);
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fractol->view.mlx_ptr,
		fractol->view.win_ptr, fractol->view.img.img_ptr, 0, 0);
}

/*
 * Clean up and destroy view resources
 */
void	destroy_view(t_view *view)
{
	if (view->img.img_ptr)
		mlx_destroy_image(view->mlx_ptr, view->img.img_ptr);
	if (view->win_ptr)
		mlx_destroy_window(view->mlx_ptr, view->win_ptr);
	if (view->mlx_ptr)
	{
		mlx_destroy_display(view->mlx_ptr);
		free(view->mlx_ptr);
	}
}
