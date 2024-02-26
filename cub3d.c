/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molla <molla@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 09:16:16 by molla             #+#    #+#             */
/*   Updated: 2024/02/26 16:31:45 by molla            ###   ########.fr       */
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
	printf("PUT IMG\n");
	return (0);
}

int	keypress(int keycode, t_cub *cub)
{
	double rotSpeed	= 0.1;

	if (keycode == ESCAPE)
	{
		mlx_destroy_window(cub->win.mlx_ptr, cub->win.win_ptr);
		exit(0);
	}
	else if (keycode == W)
	{
		printf("W\n");
		if (cub->map.arr[(int)cub->game.posy][(int)(cub->game.posx + cub->game.dirx * 0.2)] != '1')
			cub->game.posx += cub->game.dirx * 0.1;
		if (cub->map.arr[(int)(cub->game.posy + cub->game.diry * 0.2)][(int)cub->game.posx] != '1')
			cub->game.posy += cub->game.diry * 0.1;
		printf("posx = %f   ||   posy = %f", cub->game.posx, cub->game.posy);
	}
	else if (keycode == S)
	{
		printf("S\n");
		if (cub->map.arr[(int)cub->game.posy][(int)(cub->game.posx - cub->game.dirx * 0.2)] != '1')
			cub->game.posx -= cub->game.dirx * 0.1;
		if (cub->map.arr[(int)(cub->game.posy - cub->game.diry * 0.2)][(int)cub->game.posx] != '1')
			cub->game.posy -= cub->game.diry * 0.1;
	}
	else if (keycode == A)
	{
		if (cub->map.arr[(int)(cub->game.posy)][(int)(cub->game.posx + cub->game.diry * 0.2)] != '1')
			cub->game.posx += cub->game.diry * 0.1;
		if (cub->map.arr[(int)(cub->game.posy - cub->game.dirx * 0.2)][(int)(cub->game.posx)] != '1')
			cub->game.posy -= cub->game.dirx * 0.1;
		printf("A\n");
	}
	else if (keycode == D)
	{
		if (cub->map.arr[(int)(cub->game.posy)][(int)(cub->game.posx - cub->game.diry * 0.2)] != '1')
			cub->game.posx -= cub->game.diry * 0.1;
		if (cub->map.arr[(int)(cub->game.posy + cub->game.dirx * 0.2)][(int)(cub->game.posx)] != '1')
			cub->game.posy += cub->game.dirx * 0.1;
		printf("D\n");
	}
	else if (keycode == LEFT)
	{
		double olddirx = cub->game.dirx;
		cub->game.dirx = cub->game.dirx * cos(rotSpeed) - cub->game.diry * sin(rotSpeed);
		cub->game.diry = olddirx * sin(rotSpeed) + cub->game.diry * cos(rotSpeed);
		double oldplanx = cub->game.planx;
		cub->game.planx = cub->game.planx * cos(rotSpeed) - cub->game.plany * sin(rotSpeed);
		cub->game.plany = oldplanx * sin(rotSpeed) + cub->game.plany * cos(rotSpeed);
		printf("LEFT\n");
	}
	else if (keycode == RIGHT)
	{
		double olddirx = cub->game.dirx;
		cub->game.dirx = cub->game.dirx * cos(-rotSpeed) - cub->game.diry * sin(-rotSpeed);
		cub->game.diry = olddirx * sin(-rotSpeed) + cub->game.diry * cos(-rotSpeed);
		double oldplanx = cub->game.planx;
		cub->game.planx = cub->game.planx * cos(-rotSpeed) - cub->game.plany * sin(-rotSpeed);
		cub->game.plany = oldplanx * sin(-rotSpeed) + cub->game.plany * cos(-rotSpeed);
		printf("LEFT\n");
		printf("RIGHT\n");
	}
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
	render(&cub);
	mlx_key_hook(cub.win.win_ptr, &keypress, &cub);
	mlx_hook(cub.win.win_ptr, 17, 0, close_window, NULL);
	mlx_loop(cub.win.mlx_ptr);
	return (0);
}
