/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotations.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molla <molla@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 10:49:02 by molla             #+#    #+#             */
/*   Updated: 2024/02/28 10:50:01 by molla            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	left_rot(t_cub *cub)
{
	double	olddirx;
	double	oldplanx;

	olddirx = cub->game.dirx;
	cub->game.dirx = cub->game.dirx * cos(0.1) - cub->game.diry * sin(0.1);
	cub->game.diry = olddirx * sin(0.1) + cub->game.diry * cos(0.1);
	oldplanx = cub->game.planx;
	cub->game.planx = cub->game.planx * cos(0.1) - cub->game.plany * sin(0.1);
	cub->game.plany = oldplanx * sin(0.1) + cub->game.plany * cos(0.1);
}

void	right_rot(t_cub *cub)
{
	double	olddirx;
	double	oldplanx;

	olddirx = cub->game.dirx;
	cub->game.dirx = cub->game.dirx * cos(-0.1) - cub->game.diry * sin(-0.1);
	cub->game.diry = olddirx * sin(-0.1) + cub->game.diry * cos(-0.1);
	oldplanx = cub->game.planx;
	cub->game.planx = cub->game.planx * cos(-0.1) - cub->game.plany * sin(-0.1);
	cub->game.plany = oldplanx * sin(-0.1) + cub->game.plany * cos(-0.1);
}
