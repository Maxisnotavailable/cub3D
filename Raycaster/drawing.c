/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molla <molla@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 14:04:19 by molla             #+#    #+#             */
/*   Updated: 2024/02/28 19:16:19 by molla            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	convert_to_color(int color[3])
{
	unsigned char	red;
	unsigned char	green;
	unsigned char	blue;
	int				coolor;

	red = (unsigned char)color[0];
	green = (unsigned char)color[1];
	blue = (unsigned char)color[2];
	coolor = (red << 16) | (green << 8) | blue;
	return (coolor);
}

void	establishement_draw(t_cub *cub)
{
	if (cub->game.side == 0)
		cub->game.perpwalldist = (cub->game.sidedistx - cub->game.deltadistx);
	else
		cub->game.perpwalldist = (cub->game.sidedisty - cub->game.deltadisty);
	cub->game.lineheight = (int)(cub->win.height / cub->game.perpwalldist);
	cub->game.drawstart = (-cub->game.lineheight / 2) + (cub->win.height / 2);
	if (cub->game.drawstart < 0)
		cub->game.drawstart = 0;
	cub->game.drawend = (cub->game.lineheight / 2) + (cub->win.height / 2);
	if (cub->game.drawend >= cub->win.height)
		cub->game.drawend = cub->win.height - 1;
	return ;
}

void	my_pixel_put(t_cub *cub, int x, int y, int color)
{
	char	*pixel;

	pixel = cub->win.img.addr + (y * cub->win.img.line_len + x
			* (cub->win.img.bpp / 8));
	*(int *)pixel = color;
	return ;
}

unsigned int	get_pixel_color(t_img img, int x, int y)
{
	char	*color;

	color = img.addr + (y * img.line_len + x * (img.bpp / 8));
	return (*(unsigned int *)color);
}

void	draw_verline(t_cub *cub, int x)
{
	int				start;
	int				end;
	unsigned int	color;

	end = cub->win.height;
	start = -1;
	while (++start < cub->game.drawstart)
		my_pixel_put(cub, x, start, cub->game.c_color);
	while (cub->game.drawstart < cub->game.drawend)
	{
		cub->game.texy = (int)cub->game.texpos & (64 - 1);
		cub->game.texpos += cub->game.step;
		color = get_pixel_color(find_texture(cub),
				cub->game.texx, cub->game.texy);
		my_pixel_put(cub, x, cub->game.drawstart, color);
		cub->game.drawstart++;
	}
	while (cub->game.drawend <= end)
	{
		my_pixel_put(cub, x, cub->game.drawend, cub->game.f_color);
		cub->game.drawend++;
	}
	return ;
}
