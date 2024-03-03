/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molla <molla@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/14 08:35:16 by molla             #+#    #+#             */
/*   Updated: 2024/03/03 15:08:01 by molla            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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

void	init_elems(t_cub *cub)
{
	cub->elem.no = 1;
	cub->elem.so = 1;
	cub->elem.we = 1;
	cub->elem.ea = 1;
	cub->elem.f = 1;
	cub->elem.c = 1;
	cub->elem.all = 1;
	cub->elem.nb_line = 0;
	cub->map.map = 1;
	cub->map.nb_line = 0;
	cub->map.player = '0';
	cub->map.arr = NULL;
	cub->elem.path_no = NULL;
	cub->elem.path_so = NULL;
	cub->elem.path_ea = NULL;
	cub->elem.path_we = NULL;
}

int	parsing(int argc, char **argv, t_cub *cub)
{
	init_elems(cub);
	if (check_arg(argc, argv) == 1)
		return (1);
	if (check_elems(argv, cub) == 1)
		return (1);
	return (0);
}
