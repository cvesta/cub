/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvesta <cvesta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/25 16:15:26 by cvesta            #+#    #+#             */
/*   Updated: 2021/04/27 21:45:25 by cvesta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int							bmp(t_cub *cub)
{
	int						fd;
	unsigned int			pix_line;
	unsigned int			fill_bytes_line;

	fd = open("cub3d.bmp", O_WRONLY | O_CREAT | O_TRUNC, 0755);
	if (fd == -1)
		return (0);
	pix_line = cub->width * sizeof(t_pixel);
	fill_bytes_line = (4 - (pix_line % 4)) % 4;
	type_header(fd, cub, pix_line, fill_bytes_line);
	save_pixels(fd, cub, pix_line, fill_bytes_line);
	close(fd);
	return (1);
}

static unsigned char		*make_header(void)
{
	static unsigned char	header[54];
	int						a;

	a = 0;
	while (a < 29)
		header[a++] = 0;
	header[0] = 66;
	header[1] = 77;
	header[10] = 54;
	header[14] = 40;
	header[26] = 1;
	header[28] = 24;
	return (header);
}

void						type_header(int fd, t_cub *cub,
											unsigned int pix_line,
											unsigned int fill_bytes_line)
{
	unsigned int			*file_record_size;
	unsigned int			*entrance_width;
	unsigned int			*entrance_height;
	static unsigned char	*header;

	header = make_header();
	file_record_size = (unsigned int *)&header[2];
	*file_record_size = 54 + (pix_line + fill_bytes_line)\
	* (cub->height - 1);
	entrance_width = (unsigned int *)&header[18];
	*entrance_width = cub->width;
	entrance_height = (unsigned int *)&header[22];
	*entrance_height = (cub->height - 1);
	write(fd, header, 54);
}

void						save_pixels(int fd, t_cub *cub,
							unsigned int pix_line,
							unsigned int fill_bytes_line)
{
	t_pixel					array[cub->height - 1][cub->width];
	int						i;
	int						j;
	static unsigned char	nools[3];
	int						addr;

	i = 0;
	while (i < 3)
		nools[i++] = 0;
	i = 0;
	while (i < cub->height - 1)
	{
		j = 0;
		while (j < cub->width)
		{
			addr = (cub->height - 1 - i) * cub->image.len_line\
			+ j * (cub->image.bpp / 8);
			array[i][j].r = (cub->image.addr[addr]);
			array[i][j].g = (cub->image.addr[addr + 1]);
			array[i][j].b = (cub->image.addr[addr + 2]);
			j++;
		}
		write(fd, array[i++], pix_line);
		write(fd, nools, fill_bytes_line);
	}
}
