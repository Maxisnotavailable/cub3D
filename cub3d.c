/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molla <molla@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 09:16:16 by molla             #+#    #+#             */
/*   Updated: 2024/02/15 11:01:13 by molla            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(int keycode, void *param)
{
	(void)keycode;
	(void)param;
	exit(0);
}

void	init_game(t_cub *cub)
{
	cub->time.time = 0;
	cub->time.old_time = 0;
	cub->game.dirx = -1;
	cub->game.diry = -0;
	cub->game.planx = 0;
	cub->game.plany = 0.66;
	cub->game.posx = cub->map.posx_init;
	cub->game.posx = cub->map.posy_init;
	return ;
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (parsing(argc, argv, &cub) == 1)
		return (1);
	init_game(&cub);
	cub.win.mlx_ptr = mlx_init();
	cub.win.win_ptr = mlx_new_window(cub.win.mlx_ptr, 1538, 864, "CUB3D");
	mlx_hook(cub.win.win_ptr, 17, 0, close_window, NULL);
	mlx_loop(cub.win.mlx_ptr);
	return (0);
}
