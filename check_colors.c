/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molla <molla@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/10 16:54:04 by molla             #+#    #+#             */
/*   Updated: 2024/02/12 10:56:12 by molla            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_f_color(t_map *map, char *map_line, int i, int x)
{
	char	*color;
	int		nb_char;
	int		j;
	int		k;

	j = i;
	nb_char = 0;
	while ((map_line[i] >= '0' && map_line[i++] <= '9'))
		nb_char++;
	if (nb_char == 0 || nb_char > 3)
		return (write(2, "Error\nError in F description\n", 29), 1);
	color = malloc(sizeof(char) * nb_char + 1);
	if (!color)
		return (write(2, "Error\nMalloc failed\n", 20), 1);
	k = -1;
	while (++k < nb_char)
		color[k] = map_line[j++];
	color[k] = '\0';
	map->elem.rgb_f[x] = atoi(color);
	if (map->elem.rgb_f[x] > 255)
		return (write(2, "Error\nError in F description\n", 29), 1);
	free(color);
	return (i);
}

int	check_c_color(t_map *map, char *map_line, int i, int x)
{
	char	*color;
	int		nb_char;
	int		j;
	int		k;

	j = i;
	nb_char = 0;
	while ((map_line[i] >= '0' && map_line[i++] <= '9'))
		nb_char++;
	if (nb_char == 0 || nb_char > 3)
		return (write(2, "Error\nError in C description\n", 29), 1);
	color = malloc(sizeof(char) * nb_char + 1);
	if (!color)
		return (write(2, "Error\nMalloc failed\n", 20), 1);
	k = -1;
	while (++k < nb_char)
		color[k] = map_line[j++];
	color[k] = '\0';
	map->elem.rgb_c[x] = atoi(color);
	if (map->elem.rgb_c[x] > 255)
		return (write(2, "Error\nError in C description\n", 29), 1);
	free(color);
	return (i);
}

int	check_colors_sep(char *map_line, int i, int x)
{
	while (map_line[i] == ' ')
		i++;
	if (map_line[i] == ',')
		i++;
	else
	{
		if (x == 1)
			return (write(2, "Error\nError in F description\n", 29), 1);
		if (x == 2)
			return (write(2, "Error\nError in C description\n", 29), 1);
	}
	while (map_line[i] == ' ')
		i++;
	return (i);
}

int	check_f_description(t_map *map, char *map_line, int i)
{
	if (map->elem.f == 0)
		return (write(2, "Error\nF description is duplicated\n", 34), 1);
	if (map_line[i] != ' ')
		return (write(2, "Error\nError in F description\n", 29), 1);
	while (map_line[i] == ' ')
		i++;
	i = check_f_color(map, map_line, i, 0);
	if (i == 1)
		return (1);
	i = check_colors_sep(map_line, i, 1);
	if (i == 1)
		return (1);
	i = check_f_color(map, map_line, i, 1);
	if (i == 1)
		return (1);
	i = check_colors_sep(map_line, i, 1);
	if (i == 1)
		return (1);
	i = check_f_color(map, map_line, i, 2);
	if (i == 1)
		return (1);
	if (map_line[i] != '\n')
		return (write(2, "Error\nError in F description\n", 29), 1);
	map->elem.f = 0;
	return (0);
}

int	check_c_description(t_map *map, char *map_line, int i)
{
	if (map->elem.c == 0)
		return (write(2, "Error\nC description is duplicated\n", 34), 1);
	if (map_line[i] != ' ')
		return (write(2, "Error\nError in C description\n", 29), 1);
	while (map_line[i] == ' ')
		i++;
	i = check_c_color(map, map_line, i, 0);
	if (i == 1)
		return (1);
	i = check_colors_sep(map_line, i, 2);
	if (i == 1)
		return (1);
	i = check_c_color(map, map_line, i, 1);
	if (i == 1)
		return (1);
	i = check_colors_sep(map_line, i, 2);
	if (i == 1)
		return (1);
	i = check_c_color(map, map_line, i, 2);
	if (i == 1)
		return (1);
	if (map_line[i] != '\n')
		return (write(2, "Error\nError in C description\n", 29), 1);
	map->elem.c = 0;
	return (0);
}
