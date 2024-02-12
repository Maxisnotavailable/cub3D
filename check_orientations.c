/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_orientations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molla <molla@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 17:03:34 by molla             #+#    #+#             */
/*   Updated: 2024/02/12 10:54:30 by molla            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_no_description(t_map *map, char *map_line, int i, int j)
{
	int		nb_char_path;

	nb_char_path = 0;
	if (map->elem.no == 0)
		return (write(2, "Error\nNO description is duplicated\n", 35), 1);
	if (map_line[i] != ' ')
		return (write(2, "Error\nError in NO description\n", 30), 1);
	while (map_line[i] == ' ')
		i++;
	if (map_line[i] != '.' || map_line[i + 1] != '/')
		return (write(2, "Error\nNO description is not a path\n", 35), 1);
	i -= 1;
	j = i;
	while (map_line[++i] != '\n')
		nb_char_path++;
	map->elem.path_no = malloc(sizeof(char) * nb_char_path + 1);
	if (!map->elem.path_no)
		return (write(2, "Error\nMalloc failed\n", 19), 1);
	i = -1;
	while (++i < nb_char_path)
		map->elem.path_no[i] = map_line[++j];
	map->elem.path_no[i] = '\0';
	map->elem.no = 0;
	return (0);
}

int	check_so_description(t_map *map, char *map_line, int i, int j)
{
	int		nb_char_path;

	nb_char_path = 0;
	if (map->elem.so == 0)
		return (write(2, "Error\nSO description is duplicated\n", 35), 1);
	if (map_line[i] != ' ')
		return (write(2, "Error\nError in SO description\n", 30), 1);
	while (map_line[i] == ' ')
		i++;
	if (map_line[i] != '.' || map_line[i + 1] != '/')
		return (write(2, "Error\nSO description is not a path\n", 35), 1);
	i -= 1;
	j = i;
	while (map_line[++i] != '\n')
		nb_char_path++;
	map->elem.path_so = malloc(sizeof(char) * nb_char_path + 1);
	if (!map->elem.path_so)
		return (write(2, "Error\nMalloc failed\n", 19), 1);
	i = -1;
	while (++i < nb_char_path)
		map->elem.path_so[i] = map_line[++j];
	map->elem.path_so[i] = '\0';
	map->elem.so = 0;
	return (0);
}

int	check_we_description(t_map *map, char *map_line, int i, int j)
{
	int		nb_char_path;

	nb_char_path = 0;
	if (map->elem.we == 0)
		return (write(2, "Error\nWE description is duplicated\n", 35), 1);
	if (map_line[i] != ' ')
		return (write(2, "Error\nError in WE description\n", 30), 1);
	while (map_line[i] == ' ')
		i++;
	if (map_line[i] != '.' || map_line[i + 1] != '/')
		return (write(2, "Error\nWE description is not a path\n", 35), 1);
	i -= 1;
	j = i;
	while (map_line[++i] != '\n')
		nb_char_path++;
	map->elem.path_we = malloc(sizeof(char) * nb_char_path + 1);
	if (!map->elem.path_we)
		return (write(2, "Error\nMalloc failed\n", 19), 1);
	i = -1;
	while (++i < nb_char_path)
		map->elem.path_we[i] = map_line[++j];
	map->elem.path_we[i] = '\0';
	map->elem.we = 0;
	return (0);
}

int	check_ea_description(t_map *map, char *map_line, int i, int j)
{
	int		nb_char_path;

	nb_char_path = 0;
	if (map->elem.ea == 0)
		return (write(2, "Error\nEA description is duplicated\n", 35), 1);
	if (map_line[i] != ' ')
		return (write(2, "Error\nError in EA description\n", 30), 1);
	while (map_line[i] == ' ')
		i++;
	if (map_line[i] != '.' || map_line[i + 1] != '/')
		return (write(2, "Error\nEA description is not a path\n", 35), 1);
	i -= 1;
	j = i;
	while (map_line[++i] != '\n')
		nb_char_path++;
	map->elem.path_ea = malloc(sizeof(char) * nb_char_path + 1);
	if (!map->elem.path_ea)
		return (write(2, "Error\nMalloc failed\n", 19), 1);
	i = -1;
	while (++i < nb_char_path)
		map->elem.path_ea[i] = map_line[++j];
	map->elem.path_ea[i] = '\0';
	map->elem.ea = 0;
	return (0);
}
