/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gdetourn <gdetourn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 11:36:20 by gpeyre            #+#    #+#             */
/*   Updated: 2024/05/16 16:37:10 by gdetourn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_BONUS_H
# define CUB3D_BONUS_H

# include "../minilibx-linux/mlx.h"
# include "../libft/libft.h"
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <X11/Xlib.h>
# include <X11/keysym.h>

# define BUFFER_SIZE	42
# define SQUARE_SIZE	64
# define FOV			60

/* SCREEN */

# define SCREEN_HEIGHT 	720
# define SCREEN_WIDTH 	1080

/* KEYBOARD */

# define ESC			65307
# define RIGHT			65363
# define LEFT			65361
# define A				97
# define D				100
# define S				115
# define W				119
# define SPACE			32

/* texture door adresse */

# define D1_PATH "./texture/exit_c.xpm"

/* MINIMAP */

typedef struct s_mnmap
{
	int			height;
	int			width;
	int			minixo;
	int			miniyo;
	int			mapsx;
	int			mapsy;
	float		px_x;
	float		px_y;
	double		radius;
}				t_mnmap;

/* GAME */

/* keyboard struct */

typedef struct s_key
{
	int			w;
	int			s;
	int			a;
	int			d;
	int			right;
	int			left;
	int			space;
}				t_key;

/* texture struct */

typedef struct s_img_t
{
	void		*pt_img;
	int			*address;
	int			height;
	int			width;
	int			bits_per_pixel;
	int			size_line;
	int			endian;
}				t_img_t;

/* image on the screen struct */

typedef struct s_img_s
{
	void		*pt_img;
	char		*address;
	int			height;
	int			width;
	int			bits_per_pixel;
	int			size_line;
	int			endian;

}				t_img_s;

/* Raycasting */

typedef struct s_player
{
	size_t			map_x;
	size_t			map_y;
	int				px_x;
	int				px_y;
	double			angle;
	float			fov_rd;
}				t_player;

typedef struct s_ray
{
	double			ray_ngl;
	double			distance;
	int				flag;
	int				is_door;
}				t_ray;

typedef struct s_door
{
	double			x;
	double			y;
	struct s_door	*next;
}				t_door;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	char			**scene;
	size_t			lgst_line;
	int				line_nb;
	unsigned long	floor_hex;
	unsigned long	ceiling_hex;
	unsigned long	color;
	int				text_x;
	int				text_y;
	double			h_x;
	double			h_y;
	double			v_x;
	double			v_y;
	double			wall_h;
	char			**text_tab;
	int				no;
	int				so;
	int				we;
	int				ea;
	int				f;
	int				c;
	int				texture_number;
	int				wall[4][SQUARE_SIZE * SQUARE_SIZE];
	int				door[1][SQUARE_SIZE * SQUARE_SIZE];
	t_img_t			text_door[1];
	t_img_t			img_t[4];
	t_img_s			img_s;
	t_mnmap			*mnmap;
	t_key			key;
	t_player		player;
	t_ray			ray;
	t_door			*doorlist;
	int				pass_door;
}				t_data;

/* cub3d.c */
int		on_destroy(t_data *data);
int		on_keyrelease(int keysym, t_data *data);
int		on_keypress(int keysym, t_data *data);
int		game(t_data *data);

/* display.c */
void	get_texture_nb(t_data *data, int flag);
void	get_text_x(t_data *data);
void	draw_wall_stripe(t_data *data, int ray, int t_pix, int b_pix);
float	nor_angle(float angle);
void	render_wall(t_data *data, int ray);

/* display_door.c */
void	get_door_x(t_data *data);
void	draw_door(t_data *data, int ray, int t_pix, int b_pix);
void	render_door(t_data *data, int ray);
void	ft_open_door(t_data *data);
void	init_door(t_data *data);

/* error_2.c */
void	ft_free_if_null(t_data *data);
int		first_last_line(t_data *data, size_t cur_line);
int		other_line(t_data *data, size_t cur_line);
int		other_line_2(t_data *data, size_t line, int i);
int		check_walls(t_data *data);

/* error.c */
void	print_error(const char *error, t_data *data);
int		check_error_file(int argc, char **argv);
int		is_valid_char(char **map);
int		is_double(char **map);
void	check_error_map(t_data *data);

/* get_next_line.c */
char	*get_next_line(int fd);

/* img_to_create */
void	ft_place_pixel(t_data *data, int ray, int y, int color);
void	ft_pixel(t_data *data, int color, int i, int j);
void	put_ceiling_and_floor(t_data *data);

/* init_data.c */
void	data_init(t_data *data, char **argv);
void	init_player(t_data *data);
void	extract_textures(t_data *data, char *file);

/* init_map.c */
int		is_map(char *line);
int		count_line_map(t_data *data, char *file);
void	find_lgst_line(t_data *data, char *file);
void	fill_in_map(t_data *data, int fd, char *cur_line);
int		extract_map(t_data *data, char *file);

/* init_texture_1.c */
void	convert_colors(t_data *data, char **color_tab, char c);
int		valid_colors(t_data *data, char *line);
int		valid_texture_we(t_data *data, char *line, char *dup);
int		valid_texture_ns(t_data *data, char *line);
int		check_scene_infos(t_data *data, char *file);

/* init_texture_2.c */
void	texture_init_door(t_data *data, char **argv);
void	get_text_door_addr(t_data *data);
void	fill_door_array(t_data *data);

/* minimap.c */
void	ft_put_player(t_data *data);
void	ft_init_minimap_and_player(t_data *data);
void	ft_print_minimap(t_data *data);

/* minimap_walls.c */
void	ft_pixel_mnmap(t_data *data, int color);
void	ft_read_map(t_data *data, int io, int jo);
void	ft_walls(t_data *data);

/* movements_1.c */
void	ft_movements(t_data *data);
void	ft_move_left(t_data *data);
void	ft_move_right(t_data *data);
void	ft_move_backwards(t_data *data);
void	ft_move_forward(t_data *data);

/* movements_2.c */
void	ft_rotate_left(t_data *data);
void	ft_rotate_right(t_data *data);
void	ft_init_keys(t_data *data);
void	floor_is_open_door(t_data *data);
void	ft_close_door(t_data *data);

/* raycasting_1.c */
int		wall_hit(t_data *data, float x, float y);
double	dist_ray(t_data *data, float x, float y);
double	get_dist_h_inter(t_data *data, float angle);
double	get_dist_v_inter(t_data *data, float angle);
void	raycasting(t_data *data);

/* raycasting_2.c */
int		dir_step_first(float angle, float *inter, float *step, int is_horizon);
int		dir_step_second(float angle, int is_horizon);

/* racasting_door.c */
void	raycasting_door(t_data *data);
int		door_hit(t_data *data, float x, float y);
double	get_dist_h_inter_door(t_data *data, float angle);
double	get_dist_v_inter_door(t_data *data, float angle);
int		find_door(t_data *data);

/* utils_lst_bonus.c */
t_door	*new_door(double x, double y);
void	add_door(t_door **doorlist, t_door *newdoor);
void	clear_list(t_door *doorlist);

/* utils.c */
int		ft_tab_size(char **tab);
void	clear_tab(char **tab);
size_t	count_line_tab(char **tab);

#endif