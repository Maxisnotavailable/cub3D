/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elems.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molla <molla@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 16:50:22 by molla             #+#    #+#             */
/*   Updated: 2024/02/10 18:04:18 by molla            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_orientations(t_map *map, char *map_line)
{
	if ((map_line[0] == 'N' && map_line[1] == 'O'))
	{
		if (check_no_description(map, map_line, 2, -1) == 1)
			return (1);
	}
	else if (map_line[0] == 'S' && map_line[1] == 'O')
	{
		if (check_so_description(map, map_line, 2, -1) == 1)
			return (1);
	}
	else if ((map_line[0] == 'W' && map_line[1] == 'E'))
	{
		if (check_we_description(map, map_line, 2, -1) == 1)
			return (1);
	}
	else if ((map_line[0] == 'E' && map_line[1] == 'A'))
	{
		if (check_ea_description(map, map_line, 2, -1) == 1)
			return (1);
	}
	return (0);
}

int	check_f_and_c(t_map *map, char *map_line)
{
	if (map_line[0] == 'F')
	{
		if (check_f_description(map, map_line, 1) == 1)
			return (1);
	}
	else
	{
		if (check_c_description(map, map_line, 1) == 1)
			return (1);
	}
	return (0);
}

int	check(t_map *map, char *map_line)
{
	if (map_line[0] == ' ' || map_line[0] == '1')
		return (0);
	if ((map_line[0] == 'N' && map_line[1] == 'O')
		|| (map_line[0] == 'S' && map_line[1] == 'O')
		|| (map_line[0] == 'W' && map_line[1] == 'E')
		|| (map_line[0] == 'E' && map_line[1] == 'A'))
	{
		if (check_orientations(map, map_line) == 1)
			return (1);
	}
	else if (map_line[0] == 'F' || map_line[0] == 'C')
	{
		if (check_f_and_c(map, map_line) == 1)
			return (1);
	}
	else if (map_line[0] == '\n')
		map_line[0] = '\n';
	else
		return (write(2, "Error\nError in description elements\n", 36), 1);
	return (0);
}

int	check_elems(char **argv, t_map *map)
{
	char	*map_line;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (write(2, "Error\nMap does not exist\n", 25), 1);
	map_line = get_next_line(fd);
	while (map_line != NULL)
	{
		if (check(map, map_line) == 1)
			return (1);
		map->nb_line_elem++;
		map_line = get_next_line(fd);
	}
	if (map->elem.no != 0 || map->elem.so != 0 || map->elem.we != 0
		|| map->elem.ea != 0 || map->elem.f != 0 || map->elem.c != 0)
		return (write(2, "Error\nAn item description is missing\n", 37), 1);
	return (0);
}
