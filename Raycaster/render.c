/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molla <molla@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:25:08 by molla             #+#    #+#             */
/*   Updated: 2024/02/28 19:26:39 by molla            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	render(t_cub *cub)
{
	int	x;

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
		establishment_textures(cub);
		draw_verline(cub, x);
	}
	mlx_put_image_to_window(cub->win.mlx_ptr, cub->win.win_ptr,
		cub->win.img.mlx_img, 0, 0);
	return (0);
}

int	close_window(int keycode, void *param)
{
	(void)keycode;
	(void)param;
	exit(0);
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
