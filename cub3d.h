/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 18:47:46 by cvesta            #+#    #+#             */
/*   Updated: 2021/04/27 23:22:09 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx/mlx.h"
# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>

typedef struct		s_image
{
	void			*image;
	char			*addr;
	int				bpp;
	int				len_line;
	int				endian;
	int				width;
	int				height;
}					t_image;

typedef struct		s_textures
{
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			*s;
}					t_textures;

typedef struct		s_tex
{
	t_image			*south;
	t_image			*north;
	t_image			*west;
	t_image			*east;
	t_image			*s;
}					t_tex;

typedef struct		s_keypress
{
	int				up;
	int				down;
	int				left;
	int				right;
	int				lookl;
	int				lookr;
}					t_keypress;

typedef struct		s_ray
{
	double			x_posit;
	double			y_posit;
	double			x_dir;
	double			y_dir;
	double			x_flat;
	double			y_flat;
	double			x_cam;
	double			x_raydir;
	double			y_raydir;
	int				x_map;
	int				y_map;
	double			x_side;
	double			y_side;
	double			x_deltad;
	double			y_deltad;
	double			len_ray;
	int				x_step;
	int				y_step;
	int				hit;
	int				side;
	int				height_line;
	int				draw_start;
	int				draw_end;
	double			mvspeed;
	double			x_wall;
	int				x_tex;
	int				y_tex;
	double			step;
	double			posit_tex;
	double			*zbuffer;
}					t_ray;

typedef struct		s_rsp
{
	int				numsprites;
	double			x_sprite;
	double			y_sprite;
	double			invdet;
	double			tx;
	double			ty;
	int				x_screen;
	int				height;
	int				y_start;
	int				y_end;
	int				width;
	int				x_start;
	int				x_end;
	int				x_tex;
	int				y_tex;
	int				*order;
	double			*distance;
}					t_rsp;

typedef struct		s_sprite
{
	double			x;
	double			y;
}					t_sprite;

typedef struct		s_cub
{
	void			*mlx;
	void			*cub;
	int				width;
	int				height;
	t_textures		texture;
	t_tex			tex;
	t_image			image;
	int				floor;
	int				ceiling;
	char			**map;
	int				line_size;
	t_keypress		keypress;
	t_ray			ray;
	t_rsp			rsp;
	int				save;
	t_sprite		*sprite;
}					t_cub;

typedef struct		s_pixel
{
	unsigned char	r;
	unsigned char	g;
	unsigned char	b;
}					t_pixel;

int					make_space(char c);
void				free_array(char **array);
void				free_all(t_cub *cub);
int					turn_hex(int t, int r, int g, int b);
int					wipe(t_cub *cub);

void				wipe_image(t_cub *cub);
void				wipe_textures(t_cub *cub);
void				pxl_put(t_image *image, int x, int y, int colour);

int					bmp(t_cub *cub);
void				type_header(int fd, t_cub *cub, unsigned int pix_line,
					unsigned int fill_bytes_line);
void				save_pixels(int fd, t_cub *cub, unsigned int pix_line,
					unsigned int fill_bytes_line);

int					check_argc(int argc, char *map, char *save);
int					if_arg_empty(t_cub *cub, int check_map);
int					check_number(char *str);

int					main(int argc, char **argv);

int					check_vert(int j, char **map, char *vert);
int					check_insulation(char *line);
int					check_char(char *line);
int					check_map(char **map);

int					check_map_size(char **map);
int					check_player(char **map);
int					check_angle(char **map);

void				monitor_raycast(t_cub *win, int x);
void				count_wall_pos_t(t_cub *win);
void				count_draw(t_cub *win);
void				depict_raycast(t_cub *win, int x);

int					monitor_sprites(t_cub *cub);
void				count_depict(t_cub *cub, int *order_sp, int i);
void				paint_sprites(t_cub *cub);
void				depict_sprite(t_cub *cub, int y, t_image *tex, int band);
void				run_sprites(t_cub *cub, int *order_sp);

void				move(t_cub *cub);
int					keyrelease(int keycode, t_cub *cub);
int					keypress(int keycode, t_cub *cub);

void				back(t_cub *win);
void				sidelong(t_cub *win);
void				revolve(t_cub *win, int a);

int					insert_line_to_map(t_cub *cub, char *line);
int					check_line_map(char *str);
int					read_map(int fd, t_cub *cub);
int					parser(t_cub *cub, char *map);

int					parse_arg(t_cub *cub, char *str);
int					save_to_cub(t_cub *cub, char *str, int i);

int					parse_r(t_cub *cub, char *str);
int					check_res(char **array);
int					if_res_empty(int width, int height, t_cub *cub);
int					check_max_res(int width, int height, char **array);

int					parse_tex(t_textures *texture, char *str, int a);
int					if_tex_empty(t_textures *texture, char *str, int i);
int					check_path(char *way);
int					check_extension(char *way);

int					keep_colour(t_cub *cub, char *str, char **array);
int					check_colour_max_min(char *rgb);
int					if_color_empty(t_cub *cub, char *str);
int					check_colour(char **array);
int					parse_colour(t_cub *cub, char *str);

void				classify_spr(int *order, double *dist, int amount);
int					raycast(t_cub *cub);
int					cycle(t_cub *cub);
void				img_make(t_cub *cub);
void				paint_texs(t_cub *cub);

void				setup_rsp(t_cub *cub);
void				setup_arg(t_cub *cub);
void				setup_raycast(t_cub *cub, int x);
void				setup_hit(t_cub *cub);
void				setup_sided(t_cub *cub);

t_image				*make_tex(t_cub *cub, char *way);
int					setup_textures(t_cub *cub);

int					player_position(t_cub *cub, int x, int y);
int					player_flatness(t_cub *cub, char c);
int					player_direct(t_cub *cub, char c);
int					setup_player(t_cub *cub);

void				pos_sprite(t_cub *cub);
int					count_sprite(t_cub *cub);
int					setup_sprite(t_cub *cub);
#endif
