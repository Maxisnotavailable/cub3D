/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molla <molla@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 13:57:07 by molla             #+#    #+#             */
/*   Updated: 2024/02/26 14:01:05 by molla            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	init_game(t_cub *cub)
{
	cub->win.width = 1280;
	cub->win.height = 768;
	cub->game.posx = cub->map.posx_init + 0.5;
	cub->game.posy = cub->map.posy_init + 0.5;
	cub->game.camerax = -1;
	cub->game.raydirx = 0;
	cub->game.raydiry = 0;
	cub->game.hit = 0;
	return ;
}

void	init_dir(t_cub *cub, double x, double y)
{
	cub->game.dirx = x;
	cub->game.diry = y;
	return ;
}

void	init_plan(t_cub *cub, double x, double y)
{
	cub->game.planx = x;
	cub->game.plany = y;
	return ;
}

void	init_player_orientation(t_cub *cub)
{
	if (cub->map.player == 'N')
	{
		init_dir(cub, 0, -1);
		init_plan(cub, 0.66, 0);
	}
	else if (cub->map.player == 'S')
	{
		init_dir(cub, 0, 1);
		init_plan(cub, -0.66, 0);
	}
	else if (cub->map.player == 'W')
	{
		init_dir(cub, -1, 0);
		init_plan(cub, 0, -0.66);
	}
	else if (cub->map.player == 'E')
	{
		init_dir(cub, 1, 0);
		init_plan(cub, 0, 0.66);
	}
	return ;
}

void	calculs_init(t_cub *cub, int x)
{
	cub->game.camerax = 2 * x / (double)(cub->win.width) - 1;
	cub->game.raydirx = cub->game.dirx + cub->game.planx
		* cub->game.camerax;
	cub->game.raydiry = cub->game.diry + cub->game.plany
		* cub->game.camerax;
	cub->game.mapx = (int)cub->game.posx;
	cub->game.mapy = (int)cub->game.posy;
	return ;
}
