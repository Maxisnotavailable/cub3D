/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molla <molla@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:04:19 by molla             #+#    #+#             */
/*   Updated: 2024/02/26 14:06:15 by molla            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	establishement_draw(t_cub *cub)
{
	if (cub->game.side == 0)
		cub->game.perpwalldist = (cub->game.sidedistx - cub->game.deltadistx);
	else
		cub->game.perpwalldist = (cub->game.sidedisty - cub->game.deltadisty);
	cub->game.lineheight = (int)(cub->win.height / cub->game.perpwalldist);
	cub->game.drawstart = (-cub->game.lineheight / 2) + (cub->win.height / 2);
	if (cub->game.drawstart < 0)
		cub->game.drawstart = 0;
	cub->game.drawend = (cub->game.lineheight / 2) + (cub->win.height / 2);
	if (cub->game.drawend >= cub->win.height)
		cub->game.drawend = cub->win.height - 1;
	return ;
}

void	my_pixel_put(t_cub *cub, int x, int y, int color)
{
	char	*pixel;

	pixel = cub->win.img.addr + (y * cub->win.img.line_len + x
			* (cub->win.img.bpp / 8));
	*(int *)pixel = color;
	return ;
}

void	draw_verline(t_cub *cub, int x, int color)
{
	while (cub->game.drawstart < cub->game.drawend)
	{
		my_pixel_put(cub, x, cub->game.drawstart, color);
		cub->game.drawstart++;
	}
	return ;
}
