/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molla <molla@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 09:16:16 by molla             #+#    #+#             */
/*   Updated: 2024/02/26 13:15:18 by molla            ###   ########.fr       */
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
	cub->win.width = 1280;
	cub->win.height = 768;
	cub->game.posx = cub->map.posx_init + 0.5;
	cub->game.posy = cub->map.posy_init + 0.5;
	cub->game.dirx = -1;
	cub->game.diry = 0;
	cub->game.planx = 0;
	cub->game.plany = 0.66;
	cub->game.camerax = -1;
	cub->game.raydirx = 0;
	cub->game.raydiry = 0;
	cub->game.hit = 0;
	return ;
}

int	keypress(int keycode, t_cub *cub)
{
	if (keycode == ESCAPE)
	{
		mlx_destroy_window(cub->win.mlx_ptr, cub->win.win_ptr);
		exit(0);
	}
	else if (keycode == W)
		printf("W\n");
	else if (keycode == S)
		printf("S\n");
	else if (keycode == A)
		printf("A\n");
	else if (keycode == D)
		printf("D\n");
	else if (keycode == LEFT)
		printf("LEFT\n");
	else if (keycode == RIGHT)
		printf("RIGHT\n");
	return (0);
}

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
	//printf("posx = %f || mapx = %d\n", cub->game.posx, cub->game.mapx);
	//printf("posy = %f || mapy = %d\n", cub->game.posy, cub->game.mapy);
	printf("deltaX = %f || deltaY = %f\n", cub->game.deltadistx, cub->game.deltadisty);
	if (cub->game.raydirx < 0)
	{
		cub->game.stepx = -1;
		cub->game.sidedistx = (cub->game.posx - cub->game.mapx) * cub->game.deltadistx;
	}
	else
	{
		cub->game.stepx = 1;
		cub->game.sidedistx = (cub->game.mapx + 1.0 - cub->game.posx) * cub->game.deltadistx;
	}
	printf("sidedistX = %f\n", cub->game.sidedistx);
	if (cub->game.raydiry < 0)
	{
		cub->game.stepy = -1;
		cub->game.sidedisty = (cub->game.posy - cub->game.mapy) * cub->game.deltadisty;
	}
	else
	{
		cub->game.stepy = 1;
		cub->game.sidedisty = (cub->game.mapy + 1.0 - cub->game.posy) * cub->game.deltadisty;
	}
	printf("sidedistY = %f\n", cub->game.sidedisty);
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

void	establishement_draw(t_cub * cub)
{
	printf("sidedistx = %f - deltadistx = %f || sidedisty = %f - deltadisty = %f\n", cub->game.sidedistx, cub->game.deltadistx, cub->game.sidedisty, cub->game.deltadisty);
	//printf("side = %d\n", cub->game.side);
	if (cub->game.side == 0)
		cub->game.perpwalldist = (cub->game.sidedistx - cub->game.deltadistx);
	else
		cub->game.perpwalldist = (cub->game.sidedisty - cub->game.deltadisty);
	printf("perpwalldist = %f\n", cub->game.perpwalldist);
	//printf("winheight = %d\n", cub->win.height);
	cub->game.lineheight = (int)(cub->win.height / cub->game.perpwalldist);
	printf("lineheight = %d\n", cub->game.lineheight);
	cub->game.drawstart = (-cub->game.lineheight / 2) + (cub->win.height / 2);
	if (cub->game.drawstart < 0)
		cub->game.drawstart = 0;
	cub->game.drawend = (cub->game.lineheight / 2) + (cub->win.height / 2);
	//printf("drawend = %d\n", cub->game.drawend);
	if (cub->game.drawend >= cub->win.height)
		cub->game.drawend = cub->win.height - 1;
	return ;
}

void	my_pixel_put(t_cub *cub, int x, int y, int color)
{
	char	*pixel;

	pixel = cub->win.img.addr + (y * cub->win.img.line_len + x * (cub->win.img.bpp / 8));
	*(int *)pixel = color;
	return ;
}

void	draw_verline(t_cub *cub, int x, int color)
{
	//printf("drawstart = %d || drawend = %d\n", cub->game.drawstart, cub->game.drawend);
	while (cub->game.drawstart < cub->game.drawend)
	{
		//printf("drawstart = %d || drawend = %d\n", cub->game.drawstart, cub->game.drawend);
		my_pixel_put(cub, x, cub->game.drawstart, color);
		cub->game.drawstart++;
	}
	return ;
}
void	init_player_orientation(t)

int	render(t_cub *cub)
{
	int	x;
	int	color;

	x = -1;
	cub->win.img.mlx_img = mlx_new_image(cub->win.mlx_ptr, cub->win.width, cub->win.height);
	cub->win.img.addr = mlx_get_data_addr(cub->win.img.mlx_img, &cub->win.img.bpp, &cub->win.img.line_len, &cub->win.img.endian);
	while (++x < cub->win.width)
	{
		// printf("x = %d || winwidht = %d\n", x, cub->win.width);
		cub->game.camerax = 2 * x / (double)(cub->win.width) - 1;
		printf("camerax = %f\n", cub->game.camerax);
		cub->game.raydirx = cub->game.dirx + cub->game.planx * cub->game.camerax;
		cub->game.raydiry = cub->game.diry + cub->game.plany * cub->game.camerax;
		printf("raydirx = %f || Raydiry = %f\n", cub->game.raydirx, cub->game.raydiry);
		cub->game.mapx = (int)cub->game.posx;
		cub->game.mapy = (int)cub->game.posy;
		calculate_deltas(cub);
		calculate_step_and_sidedist(cub);
		dda_algo(cub);
		establishement_draw(cub);
		color = 16711680;
		if (cub->game.side == 1)
			color = color / 2;
		draw_verline(cub, x, color);
		printf("---    VERLINE %d DRAWED    ---\n", x);
	}
	printf("before putimgtowin\n");
	mlx_put_image_to_window(cub->win.mlx_ptr, cub->win.win_ptr, cub->win.img.mlx_img, 0, 0);
	printf("after putimgtowin\n");
	return (0);
}

int	main(int argc, char **argv)
{
	t_cub	cub;

	if (parsing(argc, argv, &cub) == 1)
		return (1);
	init_game(&cub);
	cub.win.mlx_ptr = mlx_init();
	cub.win.win_ptr = mlx_new_window(cub.win.mlx_ptr, cub.win.width, cub.win.height, "CUB3D");
	render(&cub);
	mlx_key_hook(cub.win.win_ptr, &keypress, &cub);
	mlx_hook(cub.win.win_ptr, 17, 0, close_window, NULL);
	mlx_loop(cub.win.mlx_ptr);
	return (0);
}
