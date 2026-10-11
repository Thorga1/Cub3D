/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tordner <tordner@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/02 16:38:17 by tordner           #+#    #+#             */
/*   Updated: 2025/09/09 19:42:01 by tordner          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <math.h>
# include <fcntl.h>
# include "mlx.h"
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <X11/keysym.h>

# define SCREEN_WIDTH 640
# define SCREEN_HEIGHT 480
# define TEXTURE_SIZE 64
# define TILE_SIZE 64
# define FOV_ANGLE 60
# define PI 3.1415926535
# define H 720
# define W 960
# define EPS 0.0001
# define TAN_EPS 1e-6
# define INF_DIST 1e9
# define EXIT_SUCCESS 0
# define EXIT_FAIL 1
# define SPEED 0.1
# define TURN_ANGLE 32
# define MIN_PERP 1e-6

typedef struct s_player
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
}	t_player;

typedef struct s_config
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor_rgb[3];
	int		ceiling_rgb[3];
}	t_config;

typedef struct s_count_elements
{
	int	c_no;
	int	c_so;
	int	c_ea;
	int	c_we;
	int	c_floor;
	int	c_ceiling;
}	t_c_elem;

typedef struct s_ray
{
	double	dir_x;
	double	dir_y;
	double	wallhit_x;
	double	wallhit_y;
	double	distance;
	int		wallhit_side;
	int		color;
	double	intercept_x;
	double	intercept_y;
	double	wallhit_hor_dist;
	double	wallhit_ver_dist;
	int		is_facing_right;
	int		is_facing_down;
	int		texture_x;
	int		texture_y;
}	t_ray;

typedef struct s_wall
{
	int	height;
	int	top;
	int	bottom;
}	t_wall;

typedef struct s_img
{
	void	*ptr;
	char	*addr;
	int		bpp;
	int		ll;
	int		endian;
	int		width;
	int		height;
}	t_img;

typedef struct s_map
{
	char	**map;
	char	**dup_map;
	int		max_width;
	int		max_height;
}	t_map;

typedef struct s_mlx
{
	void	*ptr;
	void	*win_ptr;
}	t_mlx;

typedef struct s_ctx
{
	double	player_facing_angle;
	double	fov_start;
	double	dist_proj_plane;
	double	delta;
}	t_ctx;

typedef struct s_data
{
	int			flood_error;
	char		**input;
	t_config	conf;
	t_c_elem	c_elem;
	t_mlx		mlx;
	t_img		img;
	t_player	player;
	t_ray		ray;
	t_wall		wall;
	t_map		map;
	t_img		textures[4];
}			t_data;

int				errors(int ac, char **av);
int				ft_exit(t_data *data, int end);

char			**ft_split(char const *s, char c);
int				ft_is_alpha(char c);
int				ft_isspace(int c);
char			*ft_strdup(const char *s);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strlen(const char *str);
int				ft_atoi(const char *str);
int				ft_isdigit(int c);
void			pad_map_with_walls(char **map);

int				init_data(t_data *data);

int				handle_input(t_data *data, char **av);

int				is_map_line(const char *line);
int				is_identifier_line(const char *line);
int				is_line_empty(const char *line);
int				handle_map(t_data *data);

void			trim_trailing_spaces(char *str);
void			get_no(t_data *data, const char *line);
void			get_so(t_data *data, const char *line);
void			get_ea(t_data *data, const char *line);
void			get_we(t_data *data, const char *line);
int				get_floor(t_data *data, const char *str);
int				get_ceiling(t_data *data, const char *str);

int				get_identifiers(t_data *data, const char *line);

int				validate_texture(t_data *data, char *path, const char *label);

int				init_flood_fill(t_data *data);
int				is_spawn(char c);
void			get_player(t_data *data);
void			get_map_infos(t_data *data);	
int				ft_key(int key, t_data *data);

//mlx
void			init_mlx(t_data *data);
void			move_front(t_data *data);
void			move_back(t_data *data);
void			move_left(t_data *data);
void			move_right(t_data *data);
void			rotate_right(t_data *data);
void			rotate_left(t_data *data);

//init_game
int				init_ray(t_data *data);

//draw_game
void			draw_ceiling_and_floor(t_data *data);
void			ray_direction(t_data *data);
void			rotate_ray(t_data *data);
int				draw_game(t_data *data);

//dda
void			find_horizontal_hit(t_data *data, double xstep, double ystep);
void			horizontal_hit(t_data *data, double ray_angle, \
					double xstep, double ystep);
void			find_vertical_hit(t_data *data, double xstep, double ystep);
void			vertical_hit(t_data *data, double ray_angle, \
					double xstep, double ystep);

//draw_strip
int				get_pixel_color(t_img *img, int texture_x, int texture_y);
void			add_color_to_pixel_via_mlx(t_img *img, int row, \
					int col, unsigned int color);
void			draw_pixel(t_data *data, t_img *img, int row, int col);
void			draw_texture(t_data *data, int row, int col);
void			draw_strip(t_data *data, int col);

//fix_fisheye
double			fix_fisheye(t_data *data, double ray_angle, \
					double player_facing_angle);

//utils_1
double			ft_atan2(double y, double x);
double			to_rad(double degrees);
double			ft_tan(double ray_angle);
int				hit_horizontal_wall(t_data *data, double x, double y);
int				hit_vertical_wall(t_data *data, double x, double y);

//utils_2
void			choose_nearest_hit_dist(t_data *data, double hor_x, \
					double hor_y);
void			texture_hit_x(t_data *data);
unsigned int	rgb_to_color(int r, int g, int b);
int				is_valid_position(t_data *data, double x, double y);
void			init_texture(t_data *data, t_img *tex, char *path);
void			*ft_memset(void *b, int c, size_t len);

//dda_utils
void			protect(double a);
double			correct_xstep_sign(t_data *d, double xstep);
double			correct_ystep_sign(t_data *d, double ystep);
void			calculate_wall(double perp, t_data *data);
void			cast_hits(t_data *data, double ray_angle);

//free
void			ft_free_texutre(t_data *d);
int				ft_end(t_data *data);
int				ft_exit(t_data *data, int end);
void			free_input(char **map);
void			ft_free_all(t_data *data);
#endif
