/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molla <molla@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 10:43:38 by molla             #+#    #+#             */
/*   Updated: 2024/02/15 17:09:27 by molla            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_close(char **arr, t_line *line, int x, int y)
{
	int	posx_zero;

	posx_zero = x;
	if (y == 0 || y == line->nb_line_map - 1 || x == 0
		|| arr[y][x + 1] == '\0')
		return (write(2, "Error\nMap is open\n", 18), 1);
	else if (posx_zero > line->up || posx_zero > line->down
		|| arr[y - 1][x] == ' ' || arr[y + 1][x] == ' '
		|| arr[y][x + 1] == ' ' || arr[y][x - 1] == ' '
		|| arr[y - 1][x] == '\0' || arr[y + 1][x] == '\0'
		|| arr[y][x + 1] == '\0' || arr[y][x - 1] == '\0')
		return (write(2, "Error\nMap is open\n", 18), 1);
	return (0);
}

int	count_map_line(t_cub *cub, int fd)
{
	char	*map_line;

	map_line = get_next_line(fd);
	cub->map.nb_line++;
	while (map_line != NULL)
	{
		free(map_line);
		cub->map.nb_line++;
		map_line = get_next_line(fd);
	}
	if (close(fd) == -1)
		return (write(2, "Closed failed\n", 14), 1);
	return (0);
}

int	create(t_cub *cub, char **map_line, int fd)
{
	static int	i = 0;
	static int	j = 0;

	if (++i <= cub->elem.nb_line)
	{
		free(*map_line);
		*map_line = get_next_line(fd);
	}
	else
	{
		if (*map_line[0] == '\n')
			return (write(2, "Error\nMap is cut\n", 17), 1);
		cub->map.arr[j++] = ft_strtrim(*map_line, "\n");
		*map_line = get_next_line(fd);
	}
	return (0);
}

int	create_map_arr(t_cub *cub, int fd, char *argv)
{
	char	*map_line;

	if (count_map_line(cub, fd) == 1)
		return (1);
	cub->map.arr = malloc(sizeof (char *) * (cub->map.nb_line + 1));
	fd = open(argv, O_RDONLY);
	if (fd == -1)
		return (write(2, "Error\nMap does not exist\n", 25), 1);
	map_line = get_next_line(fd);
	while (map_line != NULL)
	{
		if (create(cub, &map_line, fd) == 1)
			return (1);
	}
	cub->map.arr[cub->map.nb_line] = NULL;
	close(fd);
	return (0);
}
