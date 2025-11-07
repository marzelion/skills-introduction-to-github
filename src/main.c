#include "../includes/fractol.h"

/*
 * Print error message and exit
 */
void	error_exit(char *message)
{
	if (message)
		printf("Error: %s\n", message);
	exit(1);
}

/*
 * Display usage information
 */
static void	print_usage(void)
{
	printf("Usage: ./fractol [mandelbrot|julia]\n");
	printf("\nFractal types:\n");
	printf("  mandelbrot - Mandelbrot set\n");
	printf("  julia      - Julia set\n");
	printf("\nControls:\n");
	printf("  ESC        - Exit program\n");
	printf("  Arrow keys - Move view\n");
	printf("  +/-        - Zoom in/out\n");
	printf("  Mouse wheel- Zoom in/out\n");
}

/*
 * Parse command line arguments
 */
static int	parse_fractal_type(char *arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		if (arg[i] >= 'A' && arg[i] <= 'Z')
			arg[i] = arg[i] + 32;
		i++;
	}
	if (!arg[0])
		return (0);
	if (arg[0] == 'm' && arg[1] == 'a')
		return (MANDELBROT);
	else if (arg[0] == 'j' && arg[1] == 'u')
		return (JULIA);
	return (0);
}

/*
 * Main entry point
 */
int	main(int argc, char **argv)
{
	t_fractol	fractol;
	int			type;

	if (argc != 2)
	{
		print_usage();
		return (1);
	}
	type = parse_fractal_type(argv[1]);
	if (!type)
	{
		printf("Error: Invalid fractal type\n\n");
		print_usage();
		return (1);
	}
	init_fractol(&fractol, type);
	if (!init_view(&fractol.view))
		error_exit("Failed to initialize MLX");
	render_fractal(&fractol);
	mlx_hook(fractol.view.win_ptr, 2, 1L << 0, key_press, &fractol);
	mlx_hook(fractol.view.win_ptr, 4, 1L << 2, mouse_hook, &fractol);
	mlx_hook(fractol.view.win_ptr, 17, 0, close_window, &fractol);
	mlx_loop(fractol.view.mlx_ptr);
	return (0);
}
