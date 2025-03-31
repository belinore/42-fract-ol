/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fract_ol.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: belinore <belinore@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 18:27:05 by belinore          #+#    #+#             */
/*   Updated: 2025/03/31 16:20:15 by belinore         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACT_OL_H
# define FRACT_OL_H

/*
To switch from linux to mac
1. Uncomment included header "./mlx/minilibx_macos/mlx.h"
	+ comment "./mlx/minilibx-linux/mlx.h"
2. Uncomment KEYCODES MACOS and comment KEYCODES LINUX
3. Comment the line calling mlx_destroy_display in
	close_window (events_2.c) and initialize_mlx (init.c)
4. Make as usual
*/

# include "../mlx/minilibx-linux/mlx.h"
//# include "../mlx/minilibx_macos/mlx.h"
# include "../ft_printf/ft_printf.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# define MAX_PALETTE_SIZE 1024
# define MAX_BASE_COLORS 6
# define ITERATIONS 50
# define WIDTH 1280
# define HEIGHT 720
# define BLENDED 1
# define STRIPED 2
# define BLACK 0x000000
# define WHITE 0xFFFFFF
# define RED 0xFF0000

//KEYCODES LINUX
# define ESC 65307
# define W_MOVE_UP 119
# define S_MOVE_DOWN 115
# define A_MOVE_LEFT 97
# define D_MOVE_RIGHT 100
# define UP_ARROW 65362
# define DOWN_ARROW 65364
# define LEFT_ARROW 65361
# define RIGHT_ARROW 65363
# define PLUS_ITERS 65451
# define MINUS_ITERS 65453
# define DOUBLE_ITERS 32
# define HALVE_ITERS 65288
# define LEFT_CLICK 1
# define RIGHT_CLICK 3
# define MIDDLE_CLICK 2
# define SCROLL_DOWN 4
# define SCROLL_UP 5
# define COLORS_1 49
# define COLORS_2 50
# define COLORS_3 51
# define COLORS_4 52
# define COLORS_5 53
# define COLORS_6 54
# define COLORS_7 55
# define COLORS_8 56
# define COLORS_0 48
# define ENTER_MOUSE_EVOLVE 65293
# define R_RESET 114

/* // KEYCODES MACOS
# define ESC 53
# define W_MOVE_UP 13
# define S_MOVE_DOWN 1
# define A_MOVE_LEFT 0
# define D_MOVE_RIGHT 2
# define UP_ARROW 126
# define DOWN_ARROW 125
# define LEFT_ARROW 123
# define RIGHT_ARROW 124
# define PLUS_ITERS 24
# define MINUS_ITERS 44
# define DOUBLE_ITERS 49
# define HALVE_ITERS 51
# define LEFT_CLICK 1
# define RIGHT_CLICK 2
# define MIDDLE_CLICK 3
# define SCROLL_DOWN 4
# define SCROLL_UP 5
# define COLORS_1 18
# define COLORS_2 19
# define COLORS_3 20
# define COLORS_4 21
# define COLORS_5 23
# define COLORS_6 22
# define COLORS_7 26
# define COLORS_8 28
# define COLORS_0 29
# define ENTER_MOUSE_EVOLVE 36
# define R_RESET 15 */

/// events
enum
{
	ON_KEYDOWN = 2,
	ON_KEYUP = 3,
	ON_MOUSEDOWN = 4,
	ON_MOUSEUP = 5,
	ON_MOUSEMOVE = 6,
	ON_EXPOSE = 12,
	ON_DESTROY = 17
};

// struct for a point (x, y) in the complex plane or a pixel in the image plane
typedef struct s_point
{
	double		x;
	double		y;
}				t_point;

// struct for a complex number (z = xr + yi)
// xr is the real number component of z for the x axis
// xy is the imaginary component of zfor the y axis
typedef struct s_complex
{
	double	xr;
	double	yi;
}				t_complex;

typedef struct s_fractal
{
	char		*name;
	char		code;
	double		max_value;
	int			iterations;
	double		x_shift;
	double		y_shift;
	double		zoom;
	t_point		min;
	t_point		max;
	t_complex	z;
	t_complex	c;
}				t_fractal;

typedef struct s_colors
{
	int			base_colors[MAX_BASE_COLORS];
	int			base_colors_count;
	int			palette[MAX_PALETTE_SIZE];
	int			palette_size;
	int			option;
}				t_colors;

// struct for the image data from mlx
// img_ptr is a pointer to the image struct
// pixel_ptr points to the actual pixel
typedef struct s_img
{
	void	*img_ptr;
	char	*pixel_ptr;
	int		bpp;
	int		line_length;
	int		endian;
}				t_img;

// master struct
typedef struct s_vars
{
	void		*mlx;
	void		*window;
	t_img		img;
	t_fractal	fractal;
	t_point		mouse;
	t_colors	colors;
	int			mouse_evolve;
}				t_vars;

// init.c
void			initialize_mlx(t_vars *vars);
void			initialize_events(t_vars *vars);
void			initialize_colors(t_vars *vars);
void			initialize_fractal_params(t_fractal *fractal);
void			print_instructions(void);

// events.c
int				key_handler(int keycode, t_vars *vars);

// events_2.c
int				mouse_handler(int mousecode, int x, int y, t_vars *env);
int				move_handler(int x, int y, t_vars *vars);
int				close_window(t_vars *vars);
void			switch_to_julia(t_vars *vars, t_fractal *prev);
void			zoom(double zoom_factor, t_vars *vars);

// render.c
void			render_fractal(t_vars *fractal);
void			add_pixels_to_image(t_vars *vars, void (*fractal)(int, int,
						t_vars *, t_fractal *));
double			scale(double unscaled_num, double new_min, double new_max,
					double old_max);
void			put_pixel(t_img *data, int x, int y, int color);

// fractals.c
void			mandelbrot(int x, int y, t_vars *vars, t_fractal *fractal);
void			julia(int x, int y, t_vars *vars, t_fractal *fractal);
void			burning_ship(int x, int y, t_vars *vars, t_fractal *fractal);
void			julia_ship(int x, int y, t_vars *vars, t_fractal *fractal);

// colors.c
int				get_color(int i, t_vars *vars);
void			set_base_colors(t_colors *color_params, int keycode);
void			generate_blended_palette(t_colors *color_params,
					t_fractal *fractal);
int				interpolate_color(int color1, int color2, double t);

// errors.c
void			error_malloc_failure(void);
void			error_input(void);
int				is_valid_input(char *str);

// utils.c
double			ft_atod(const char *str);
int				ft_strncmp(char *s1, char *s2, int n);

#endif