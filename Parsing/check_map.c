/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molla <molla@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:29:19 by molla             #+#    #+#             */
/*   Updated: 2024/02/15 10:57:04 by molla            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_map_char(t_cub *cub, char **arr, int x, int y)
{
	while (arr[++y] != NULL)
	{
		x = -1;
		while (arr[y][++x] != '\0')
		{
			if ((arr[y][x] == 'N' || arr[y][x] == 'S' || arr[y][x] == 'E'
				|| arr[y][x] == 'W') && cub->map.player == '0')
			{
				cub->map.player = arr[y][x];
				cub->map.posx_init = x;
				cub->map.posy_init = y;
			}
			else if ((arr[y][x] == 'N' || arr[y][x] == 'S' || arr[y][x] == 'E'
				|| arr[y][x] == 'W') && cub->map.player != '0')
				return (write(2, "Error\nSeveral players on the map\n", 33), 1);
			else if (arr[y][x] != ' ' && arr[y][x] != '1' && arr[y][x] != '0')
				return (write(2, "Error\nWrong character in map\n", 29), 1);
		}
	}
	if (cub->map.player == '0')
		return (write(2, "Error\nPlayer is missing\n", 24), 1);
	return (0);
}

int	check_wall(t_cub *cub, char **arr)
{
	int		x;
	int		y;
	t_line	line;

	line.nb_line_map = cub->map.nb_line;
	y = -1;
	while (arr[++y] != NULL)
	{
		if (y > 0 && y < cub->map.nb_line - 1)
		{
			line.up = ft_strlen(arr[y - 1]);
			line.down = ft_strlen(arr[y + 1]);
		}
		x = -1;
		while (arr[y][++x] != '\0')
		{
			if (arr[y][x] == '0' || arr[y][x] == 'N' || arr[y][x] == 'S'
				|| arr[y][x] == 'E' || arr[y][x] == 'W')
			{
				if (check_close(arr, &line, x, y) == 1)
					return (1);
			}
		}
	}
	return (0);
}

int	check_map(t_cub *cub, int fd, char *argv)
{
	if (create_map_arr(cub, fd, argv, 0) == 1)
		return (1);
	if (check_map_char(cub, cub->map.arr, 0, -1) == 1)
		return (1);
	if (check_wall(cub, cub->map.arr) == 1)
		return (1);
	cub->map.map = 0;
	return (0);
}
