/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molla <molla@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 19:25:08 by molla             #+#    #+#             */
/*   Updated: 2024/03/03 15:05:25 by molla            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	exit_cub(t_cub *cub)
{
	int	i;

	i = 0;
	if (cub->map.arr != NULL)
	{
		if (cub->map.arr[i] != NULL)
		{
			while (cub->map.arr[i] != NULL)
				free(cub->map.arr[i++]);
		}
		free(cub->map.arr);
	}
	if (cub->elem.path_no)
		free(cub->elem.path_no);
	if (cub->elem.path_so)
		free(cub->elem.path_so);
	if (cub->elem.path_ea)
		free(cub->elem.path_ea);
	if (cub->elem.path_we)
		free(cub->elem.path_we);
}

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
	mlx_destroy_image(cub->win.mlx_ptr, cub->win.img.mlx_img);
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
		exit_cub(cub);
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
