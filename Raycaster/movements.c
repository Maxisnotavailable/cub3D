/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movements.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molla <molla@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 10:20:27 by molla             #+#    #+#             */
/*   Updated: 2024/02/27 11:44:22 by molla            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	forward_mvt(t_cub *cub)
{
	if (cub->map.arr[(int)cub->game.posy][(int)(cub->game.posx
		+ cub->game.dirx * 0.2)] != '1')
		cub->game.posx += cub->game.dirx * 0.1;
	if (cub->map.arr[(int)(cub->game.posy
			+ cub->game.diry * 0.2)][(int)cub->game.posx] != '1')
		cub->game.posy += cub->game.diry * 0.1;
}

void	backward_mvt(t_cub *cub)
{
	if (cub->map.arr[(int)cub->game.posy][(int)(cub->game.posx
		- cub->game.dirx * 0.2)] != '1')
		cub->game.posx -= cub->game.dirx * 0.1;
	if (cub->map.arr[(int)(cub->game.posy
			- cub->game.diry * 0.2)][(int)cub->game.posx] != '1')
		cub->game.posy -= cub->game.diry * 0.1;
}

void	leftside_mvt(t_cub *cub)
{
	if (cub->map.arr[(int)(cub->game.posy)][(int)(cub->game.posx
		+ cub->game.diry * 0.2)] != '1')
		cub->game.posx += cub->game.diry * 0.1;
	if (cub->map.arr[(int)(cub->game.posy
			- cub->game.dirx * 0.2)][(int)(cub->game.posx)] != '1')
		cub->game.posy -= cub->game.dirx * 0.1;
}

void	rightside_mvt(t_cub *cub)
{
	if (cub->map.arr[(int)(cub->game.posy)][(int)(cub->game.posx
		- cub->game.diry * 0.2)] != '1')
		cub->game.posx -= cub->game.diry * 0.1;
	if (cub->map.arr[(int)(cub->game.posy
			+ cub->game.dirx * 0.2)][(int)(cub->game.posx)] != '1')
		cub->game.posy += cub->game.dirx * 0.1;
}
