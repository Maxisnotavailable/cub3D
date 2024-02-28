/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molla <molla@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:02:24 by molla             #+#    #+#             */
/*   Updated: 2024/02/28 19:25:27 by molla            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	calculate_deltas(t_cub *cub)
{
	if (cub->game.raydirx == 0)
		cub->game.deltadistx = 1e30;
	else
		cub->game.deltadistx = fabs(1 / cub->game.raydirx);
	if (cub->game.raydiry == 0)
		cub->game.deltadisty = 1e30;
	else
		cub->game.deltadisty = fabs(1 / cub->game.raydiry);
	return ;
}

void	calculate_step_and_sidedist(t_cub *cub)
{
	if (cub->game.raydirx < 0)
	{
		cub->game.stepx = -1;
		cub->game.sidedistx = (cub->game.posx - cub->game.mapx)
			* cub->game.deltadistx;
	}
	else
	{
		cub->game.stepx = 1;
		cub->game.sidedistx = (cub->game.mapx + 1.0 - cub->game.posx)
			* cub->game.deltadistx;
	}
	if (cub->game.raydiry < 0)
	{
		cub->game.stepy = -1;
		cub->game.sidedisty = (cub->game.posy - cub->game.mapy)
			* cub->game.deltadisty;
	}
	else
	{
		cub->game.stepy = 1;
		cub->game.sidedisty = (cub->game.mapy + 1.0 - cub->game.posy)
			* cub->game.deltadisty;
	}
	return ;
}

void	dda_algo(t_cub *cub)
{
	cub->game.hit = 0;
	while (cub->game.hit == 0)
	{
		if (cub->game.sidedistx < cub->game.sidedisty)
		{
			cub->game.sidedistx += cub->game.deltadistx;
			cub->game.mapx += cub->game.stepx;
			cub->game.side = 0;
		}
		else
		{
			cub->game.sidedisty += cub->game.deltadisty;
			cub->game.mapy += cub->game.stepy;
			cub->game.side = 1;
		}
		if (cub->map.arr[cub->game.mapy][cub->game.mapx] == '1')
			cub->game.hit = 1;
	}
	return ;
}
