/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molla <molla@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 09:16:16 by molla             #+#    #+#             */
/*   Updated: 2024/02/27 11:49:31 by molla            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_window(int keycode, void *param)
{
	(void)keycode;
	(void)param;
	exit(0);
}

int	render(t_cub *cub)
{
	int	x;
	int	color;

	mlx_do_key_autorepeaton(cub->win.mlx_ptr);
	x = -1;
	cub->win.img.mlx_img = mlx_new_image(cub->win.mlx_ptr,
			cub->win.width, cub->win.height);
	cub->win.img.addr = mlx_get_data_addr(cub->win.img.mlx_img,
			&cub->win.img.bpp, &cub->win.img.line_len, &cub->win.img.endian);
	while (++x < cub->win.width)
	{
		calculs_init(cub, x);
		calculate_deltas(cub);
		calculate_step_and_sidedist(cub);
		dda_algo(cub);
		establishement_draw(cub);
		color = 16711680;
		if (cub->game.side == 1)
			color = color - 100000;
		draw_verline(cub, x, color);
	}
	mlx_put_image_to_window(cub->win.mlx_ptr, cub->win.win_ptr,
		cub->win.img.mlx_img, 0, 0);
	return (0);
}

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

int	keypress(int keycode, t_cub *cub)
{
	if (keycode == ESCAPE)
	{
		mlx_destroy_window(cub->win.mlx_ptr, cub->win.win_ptr);
		exit(0);
	}
	else if (keycode == W)
		forward_mvt(cub);
	else if (keycode == S)
		backward_mvt(cub);
	else if (keycode == A)
		leftside_mvt(cub);
	else if (keycode == D)
		rightside_mvt(cub);
	else if (keycode == LEFT)
		left_rot(cub);
	else if (keycode == RIGHT)
		right_rot(cub);
	render(cub);
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (parsing(argc, argv, &cub) == 1)
		return (1);
	init_game(&cub);
	init_player_orientation(&cub);
	cub.win.mlx_ptr = mlx_init();
	cub.win.win_ptr = mlx_new_window(cub.win.mlx_ptr, cub.win.width,
			cub.win.height, "CUB3D");
	//mlx_do_key_autorepeaton(cub.win.mlx_ptr);
	render(&cub);
	mlx_key_hook(cub.win.win_ptr, &keypress, &cub);
	mlx_hook(cub.win.win_ptr, 17, 0, close_window, NULL);
	mlx_loop(cub.win.mlx_ptr);
	return (0);
}
