#include "../includes/fractol.h"

/*
 * Calculate Mandelbrot set iteration count
 * Formula: z(n+1) = z(n)^2 + c
 * Starting with z(0) = 0
 */
int	calculate_mandelbrot(t_complex c)
{
	int			iterations;
	t_complex	z;
	double		temp;

	iterations = 0;
	z.real = 0.0;
	z.imag = 0.0;
	while (iterations < MAX_ITERATIONS)
	{
		/* Check if point escapes (magnitude > 2) */
		if ((z.real * z.real + z.imag * z.imag) > 4.0)
			break ;
		/* z = z^2 + c */
		temp = z.real * z.real - z.imag * z.imag + c.real;
		z.imag = 2.0 * z.real * z.imag + c.imag;
		z.real = temp;
		iterations++;
	}
	return (iterations);
}

/*
 * Calculate Julia set iteration count
 * Formula: z(n+1) = z(n)^2 + c
 * Starting with z(0) = pixel position, c = constant
 */
int	calculate_julia(t_complex z, t_complex c)
{
	int		iterations;
	double	temp;

	iterations = 0;
	while (iterations < MAX_ITERATIONS)
	{
		/* Check if point escapes (magnitude > 2) */
		if ((z.real * z.real + z.imag * z.imag) > 4.0)
			break ;
		/* z = z^2 + c */
		temp = z.real * z.real - z.imag * z.imag + c.real;
		z.imag = 2.0 * z.real * z.imag + c.imag;
		z.real = temp;
		iterations++;
	}
	return (iterations);
}

/*
 * Convert screen coordinates to complex plane coordinates
 */
t_complex	screen_to_complex(int x, int y, t_fractal_params *params)
{
	t_complex	c;

	c.real = params->min_real + (x + params->move_x) * 
		(params->max_real - params->min_real) / WIDTH;
	c.imag = params->min_imag + (y + params->move_y) * 
		(params->max_imag - params->min_imag) / HEIGHT;
	return (c);
}

/*
 * Map iteration count to a color value
 * Uses smooth color gradient
 */
int	get_fractal_color(int iterations)
{
	int		r;
	int		g;
	int		b;
	double	t;

	if (iterations == MAX_ITERATIONS)
		return (COLOR_BLACK);
	/* Create smooth color gradient */
	t = (double)iterations / MAX_ITERATIONS;
	r = (int)(9 * (1 - t) * t * t * t * 255);
	g = (int)(15 * (1 - t) * (1 - t) * t * t * 255);
	b = (int)(8.5 * (1 - t) * (1 - t) * (1 - t) * t * 255);
	return ((r << 16) | (g << 8) | b);
}
