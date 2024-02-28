/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molla <molla@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:07:39 by molla             #+#    #+#             */
/*   Updated: 2024/02/28 19:20:10 by molla            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

t_img	stock_xpm(t_cub *cub, char *path)
{
	t_img	whatever;

	whatever.mlx_img = mlx_xpm_file_to_image(cub->win.mlx_ptr,
			path, &whatever.x, &whatever.y);
	whatever.addr = mlx_get_data_addr(whatever.mlx_img,
			&whatever.bpp, &whatever.line_len,
			&whatever.endian);
	return (whatever);
}

int	init_texture(t_cub *cub)
{
	cub->game.wall_no = stock_xpm(cub, cub->elem.path_no);
	if (cub->game.wall_no.x < 64 || cub->game.wall_no.y < 64)
	{
		printf("Textures must be 64 * 64 pixels\n");
		return (1);
	}
	cub->game.wall_so = stock_xpm(cub, cub->elem.path_so);
	if (cub->game.wall_so.x < 64 || cub->game.wall_so.y < 64)
	{
		printf("Textures must be 64 * 64 pixels\n");
		return (1);
	}
	cub->game.wall_ea = stock_xpm(cub, cub->elem.path_ea);
	if (cub->game.wall_ea.x < 64 || cub->game.wall_ea.y < 64)
	{
		printf("Textures must be 64 * 64 pixels\n");
		return (1);
	}
	cub->game.wall_we = stock_xpm(cub, cub->elem.path_we);
	if (cub->game.wall_we.x < 64 || cub->game.wall_we.y < 64)
	{
		printf("Textures must be 64 * 64 pixels\n");
		return (1);
	}
	return (0);
}

void	establishment_textures(t_cub *cub)
{
	if (cub->game.side == 0)
		cub->game.wallx = cub->game.posy + cub->game.perpwalldist
			* cub->game.raydiry;
	else
		cub->game.wallx = cub->game.posx + cub->game.perpwalldist
			* cub->game.raydirx;
	cub->game.wallx -= floor(cub->game.wallx);
	cub->game.texx = (int)(cub->game.wallx * 64);
	if (cub->game.side == 0 && cub->game.raydirx > 0)
		cub->game.texx = 64 - cub->game.texx - 1;
	if (cub->game.side == 1 && cub->game.raydiry < 0)
		cub->game.texx = 64 - cub->game.texx - 1;
	cub->game.step = 1.0 * 64 / cub->game.lineheight;
	cub->game.texpos = (cub->game.drawstart - cub->win.height / 2
			+ cub->game.lineheight / 2) * cub->game.step;
	return ;
}

t_img	find_texture(t_cub *cub)
{
	if (cub->game.side == 0 && cub->game.posx < cub->game.mapx)
		return (cub->game.wall_ea);
	else if (cub->game.side == 0 && cub->game.posx > cub->game.mapx)
		return (cub->game.wall_we);
	else if (cub->game.side == 1 && cub->game.posy > cub->game.mapy)
		return (cub->game.wall_no);
	else if (cub->game.side == 1 && cub->game.posy < cub->game.mapy)
		return (cub->game.wall_so);
	return (cub->game.wall_ea);
}
