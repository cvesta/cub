/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 18:47:46 by cvesta            #+#    #+#             */
/*   Updated: 2021/04/12 17:36:50 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlxlib/mlx.h"
# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>

#  define BUFFER_SIZE	32

typedef struct	s_texs
{
	t_image		*north;
	t_image		*south;
	t_image		*west;
	t_image		*east;
	t_image		*sprite;
}				t_texs;


typedef struct	s_textures
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*sprite;
}				t_textures;

typedef struct	s_image
{
	void		*img;
	int 		bpp;
	int 		endian;
	int 		width;
	int 		height;
	int 		len_line;
	char		*addr;
}				t_image;

typedef struct	t_raysprite
{
	int			numsprites;
	double		sprite_x;
	double		sprite_y;
	double		invdet;
	double		tx;
	double		ty;
	int			screen_x;
	int 		height;
	int 		width;
	int 		start_x;
	int			end_x;
	int 		start_y;
	int			end_y;
	int 		tex_x;
	int 		tex_y;
	int 		*order;
	double 		*distance;
}				s_raysprite;

typedef struct	s_cub
{
	t_image		img;
	void		*cub;
	void		*mlx;
	int			width;
	int			height;
	t_textures	textures;
	t_texs		texs;
	t_raysprite	raysprite;
	int			up;
	int 		down;
	char		**map;
	int			sizemapline;
	int 		save;

}				t_cub;

//get_next_line & utils
int		get_next_line(int fd, char **line);
size_t	ft_strlen(const char *str);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(const char *s1, const char *s2);
char	*ft_strcpy(char *dest, char *src);
char	*ft_strchr(const char *s, int c);

//parser
int		parser(t_cub *cub, char *map);
int		read_map(int fd, t_cub *cub);
int		check_line_map(char *str);
int		new_line_map(t_cub *cub, char line);

//parser2
int		parse_arg(t_cub *cub, char *str);
int		arg_write_cub(t_cub *cub, char *str, int i);

//parser3
int		parse_r(t_cub *cub, char *str);
int 	check_r(char **arr);
int		check_empty_r(int width, int height, t_cub *cub);
int		check_max_r(int width, int height, char **arr);

//parser4
int		parse_tex(t_textures *textures, char *str, int i);
int 	check_empty_tex(t_textures *textures, char *str, int i);
int		check_path(char *path);
int		check_extension(char *path);

//parser5
int		parse_color(t_cub *cub, char *str);
int		check_color(char **arr);
int		check_empty_color(t_cub *cub, char *str);
int		check_color_max_min(char *color);

//adds
int		make_space(char c);
void	clear_arr(char **arr);
int		turn_hex(int t, int r, int g, int b);

//check
int		check_empty_arg(t_cub *cub, int map);
int		check_argc(int ac, char *map, char *save);
int		check_number(char *num);

//map_set
int		check_map(char **map);
int 	check_char_in_line(char *line);
int		check_isolation(char *line);
int 	check_vert(int j, char **map, char *vert);

//map_set2
int		check_map_size(char **map);
int		check_player(char **map);
int		check_angle(char **map);

//main
int		main(int argc, char **argv);

//setup
void	setup_arg(t_cub *cub);

#endif
