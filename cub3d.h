/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/23 18:47:46 by cvesta            #+#    #+#             */
/*   Updated: 2021/03/30 18:11:25 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "libft/libft.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include <stdlib.h>

#  define BUFFER_SIZE	32

typedef struct	s_textures
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*sprite;
}				t_textures;

typedef struct	s_cub
{
	t_image		img;
	void		*cub;
	void		*mlx;
	int			width;
	int			height;
	t_textures	textures;
	t_texs		texs;
	int			up;
	int 		down;
	char		**map;

}				t_cub;

//typedef struct	s_set
//{
//	int			lines;
//
//	int			columns;
//	int			down_color;
//	int			up_color;
//	double		spin_speed;
//	double		walk_speed;
//	double		eye_level;
//	double		fov;
//	double		tile;
//	double		updown_speed;
//	char		**map;

//}				t_set;

typedef struct	s_image
{

}				t_image;

//typedef struct	s_player
//{
//	float		x;
//	float		y;
//	float		width;
//	float		height;
//	float		spinangle;
//	float		turnspeed;
//	float		movespeed;
//	double		spinspeed;
//	double		eyelevel;
//	int			directwalk;
//	int			directturn;
//	int			directwalk_lr;
//
//}				t_player;


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

//parser2
int		parse_arg(t_cub *cub, char *str);

//adds
int		make_space(char c);

//check
int		check_empty_arg(t_cub *cub, int map);
int		check_argc(int ac, char *map, char *save);



#endif
