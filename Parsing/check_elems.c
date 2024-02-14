/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elems.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molla <molla@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 16:50:22 by molla             #+#    #+#             */
/*   Updated: 2024/02/14 08:47:34 by molla            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	check_orientations(t_cub *cub, char *map_line)
{
	if ((map_line[0] == 'N' && map_line[1] == 'O'))
	{
		if (check_no_description(cub, map_line, 2, -1) == 1)
			return (1);
	}
	else if (map_line[0] == 'S' && map_line[1] == 'O')
	{
		if (check_so_description(cub, map_line, 2, -1) == 1)
			return (1);
	}
	else if ((map_line[0] == 'W' && map_line[1] == 'E'))
	{
		if (check_we_description(cub, map_line, 2, -1) == 1)
			return (1);
	}
	else if ((map_line[0] == 'E' && map_line[1] == 'A'))
	{
		if (check_ea_description(cub, map_line, 2, -1) == 1)
			return (1);
	}
	return (0);
}

int	check_f_and_c(t_cub *cub, char *map_line)
{
	if (map_line[0] == 'F')
	{
		if (check_f_description(cub, map_line, 1) == 1)
			return (1);
	}
	else
	{
		if (check_c_description(cub, map_line, 1) == 1)
			return (1);
	}
	return (0);
}

int	check(t_cub *cub, char *map_line, int fd, char *argv)
{
	if ((map_line[0] == 'N' && map_line[1] == 'O')
		|| (map_line[0] == 'S' && map_line[1] == 'O')
		|| (map_line[0] == 'W' && map_line[1] == 'E')
		|| (map_line[0] == 'E' && map_line[1] == 'A'))
	{
		if (check_orientations(cub, map_line) == 1)
			return (1);
	}
	else if (map_line[0] == 'F' || map_line[0] == 'C')
	{
		if (check_f_and_c(cub, map_line) == 1)
			return (1);
	}
	else if (map_line[0] == '\n')
		map_line[0] = '\n';
	else if ((map_line[0] == ' ' || map_line[0] == '1') && cub->elem.all != 0)
		return (write(2, "Error\nAn element description is missing\n", 40), 1);
	else if ((map_line[0] == ' ' || map_line[0] == '1') && cub->elem.all == 0)
	{
		if (check_map(cub, fd, argv) == 1)
			return (1);
	}
	else
		return (write(2, "Error\nError in description elements\n", 36), 1);
	return (0);
}

void	all_elems(t_cub *cub)
{
	if (cub->elem.no == 0 && cub->elem.so == 0 && cub->elem.we == 0
		&& cub->elem.ea == 0 && cub->elem.f == 0 && cub->elem.c == 0)
		cub->elem.all = 0;
	return ;
}

int	check_elems(char **argv, t_cub *cub)
{
	char	*map_line;
	int		fd;

	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
		return (write(2, "Error\nMap does not exist\n", 25), 1);
	map_line = get_next_line(fd);
	while (map_line != NULL)
	{
		if (check(cub, map_line, fd, argv[1]) == 1)
			return (1);
		cub->elem.nb_line++;
		all_elems(cub);
		map_line = get_next_line(fd);
	}
	if (cub->elem.all != 0)
		return (write(2, "Error\nAn item description is missing\n", 37), 1);
	if (cub->map.map != 0)
		return (write(2, "Error\nMap is missing\n", 21), 1);
	return (0);
}
