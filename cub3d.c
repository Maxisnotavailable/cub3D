/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molla <molla@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 09:16:16 by molla             #+#    #+#             */
/*   Updated: 2024/02/12 10:51:02 by molla            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_arg(int argc, char **argv)
{
	int	i;

	if (argc != 2)
		return (write(2, "Error\nInvalid number of arguments\n", 34), 1);
	i = ft_strlen(argv[1]);
	if (!ft_strnstr(argv[1], ".cub", i)
		|| ft_strncmp(ft_strnstr(argv[1], ".cub", i), ".cub", 5) != 0)
		return (write(2, "Error\nThe map must be in *.cub format\n", 38), 1);
	return (0);
}

void	init_elems(t_map *map)
{
	map->elem.no = 1;
	map->elem.so = 1;
	map->elem.we = 1;
	map->elem.ea = 1;
	map->elem.f = 1;
	map->elem.c = 1;
}

/*int	check_map(char **argv)
{
	
}*/

int	main(int argc, char **argv)
{
	t_map	map;

	if (check_arg(argc, argv) == 1)
		return (1);
	init_elems(&map);
	if (check_elems(argv, &map) == 1)
		return (1);
	return (0);
}
