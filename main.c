/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molla <molla@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 09:16:16 by molla             #+#    #+#             */
/*   Updated: 2024/02/28 19:26:32 by molla            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (parsing(argc, argv, &cub) == 1)
		return (exit_cub(&cub), 1);
	init_game(&cub);
	init_player_orientation(&cub);
	cub.win.mlx_ptr = mlx_init();
	cub.win.win_ptr = mlx_new_window(cub.win.mlx_ptr, cub.win.width,
			cub.win.height, "CUB3D");
	if (init_texture(&cub) == 1)
		return (1);
	render(&cub);
	mlx_hook(cub.win.win_ptr, 2, 1L >> 0, &keypress, &cub);
	mlx_hook(cub.win.win_ptr, 17, 0, close_window, &cub);
	mlx_loop(cub.win.mlx_ptr);
	return (0);
}
