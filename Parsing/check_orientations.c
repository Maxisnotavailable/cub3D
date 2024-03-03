/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_orientations.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molla <molla@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 17:03:34 by molla             #+#    #+#             */
/*   Updated: 2024/03/01 09:17:32 by molla            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	path_test(t_cub *cub, int x, int fd)
{
	if (x == 0)
		fd = open(cub->elem.path_no, O_RDONLY);
	else if (x == 1)
		fd = open(cub->elem.path_so, O_RDONLY);
	else if (x == 2)
		fd = open(cub->elem.path_we, O_RDONLY);
	else if (x == 3)
		fd = open(cub->elem.path_ea, O_RDONLY);
	if (fd == -1)
	{
		if (x == 0)
			return (write(2, "Error\nNO invalid path\n", 22), 1);
		else if (x == 1)
			return (write(2, "Error\nSO invalid path\n", 22), 1);
		else if (x == 2)
			return (write(2, "Error\nWE invalid path\n", 22), 1);
		else if (x == 3)
			return (write(2, "Error\nEA invalid path\n", 22), 1);
	}
	else
	{
		if (close(fd) == -1)
			return (write(2, "Closed failed\n", 14), 1);
	}
	return (0);
}

int	check_no_description(t_cub *cub, char *map_line, int i, int j)
{
	int		nb_char_path;

	nb_char_path = 0;
	if (cub->elem.no == 0)
		return (write(2, "Error\nNO description is duplicated\n", 35), 1);
	if (map_line[i] != ' ')
		return (write(2, "Error\nError in NO description\n", 30), 1);
	while (map_line[i] == ' ')
		i++;
	i -= 1;
	j = i;
	while (map_line[++i] != '\n')
		nb_char_path++;
	cub->elem.path_no = malloc(sizeof(char) * nb_char_path + 1);
	if (!cub->elem.path_no)
		return (write(2, "Error\nMalloc failed\n", 19), 1);
	i = -1;
	while (++i < nb_char_path)
		cub->elem.path_no[i] = map_line[++j];
	cub->elem.path_no[i] = '\0';
	if (path_test(cub, 0, 0) == 1)
		return (1);
	cub->elem.no = 0;
	return (0);
}

int	check_so_description(t_cub *cub, char *map_line, int i, int j)
{
	int		nb_char_path;

	nb_char_path = 0;
	if (cub->elem.so == 0)
		return (write(2, "Error\nSO description is duplicated\n", 35), 1);
	if (map_line[i] != ' ')
		return (write(2, "Error\nError in SO description\n", 30), 1);
	while (map_line[i] == ' ')
		i++;
	i -= 1;
	j = i;
	while (map_line[++i] != '\n')
		nb_char_path++;
	cub->elem.path_so = malloc(sizeof(char) * nb_char_path + 1);
	if (!cub->elem.path_so)
		return (write(2, "Error\nMalloc failed\n", 19), 1);
	i = -1;
	while (++i < nb_char_path)
		cub->elem.path_so[i] = map_line[++j];
	cub->elem.path_so[i] = '\0';
	if (path_test(cub, 1, 0) == 1)
		return (1);
	cub->elem.so = 0;
	return (0);
}

int	check_we_description(t_cub *cub, char *map_line, int i, int j)
{
	int		nb_char_path;

	nb_char_path = 0;
	if (cub->elem.we == 0)
		return (write(2, "Error\nWE description is duplicated\n", 35), 1);
	if (map_line[i] != ' ')
		return (write(2, "Error\nError in WE description\n", 30), 1);
	while (map_line[i] == ' ')
		i++;
	i -= 1;
	j = i;
	while (map_line[++i] != '\n')
		nb_char_path++;
	cub->elem.path_we = malloc(sizeof(char) * nb_char_path + 1);
	if (!cub->elem.path_we)
		return (write(2, "Error\nMalloc failed\n", 19), 1);
	i = -1;
	while (++i < nb_char_path)
		cub->elem.path_we[i] = map_line[++j];
	cub->elem.path_we[i] = '\0';
	if (path_test(cub, 2, 0) == 1)
		return (1);
	cub->elem.we = 0;
	return (0);
}

int	check_ea_description(t_cub *cub, char *map_line, int i, int j)
{
	int		nb_char_path;

	nb_char_path = 0;
	if (cub->elem.ea == 0)
		return (write(2, "Error\nEA description is duplicated\n", 35), 1);
	if (map_line[i] != ' ')
		return (write(2, "Error\nError in EA description\n", 30), 1);
	while (map_line[i] == ' ')
		i++;
	i -= 1;
	j = i;
	while (map_line[++i] != '\n')
		nb_char_path++;
	cub->elem.path_ea = malloc(sizeof(char) * nb_char_path + 1);
	if (!cub->elem.path_ea)
		return (write(2, "Error\nMalloc failed\n", 19), 1);
	i = -1;
	while (++i < nb_char_path)
		cub->elem.path_ea[i] = map_line[++j];
	cub->elem.path_ea[i] = '\0';
	if (path_test(cub, 3, 0) == 1)
		return (1);
	cub->elem.ea = 0;
	return (0);
}
