/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molla <molla@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 08:57:06 by molla             #+#    #+#             */
/*   Updated: 2024/02/10 18:08:05 by molla            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx-linux/mlx.h"
# include "Libft/libft.h"
# include <fcntl.h>

typedef struct s_elems
{
	char	*path_no;
	char	*path_so;
	char	*path_we;
	char	*path_ea;
	int		rgb_f[3];
	int		rgb_c[3];
	int		no;
	int		so;
	int		we;
	int		ea;
	int		f;
	int		c;
}	t_elems;

typedef struct s_map
{
	void		*mlx_ptr;
	void		*win_ptr;
	char		**map;
	int			nb_line_elem;
	t_elems		elem;
}	t_map;

//+++++  check_orientations.c  +++++//

int	check_no_description(t_map *map, char *map_line, int i, int j);
int	check_so_description(t_map *map, char *map_line, int i, int j);
int	check_we_description(t_map *map, char *map_line, int i, int j);
int	check_ea_description(t_map *map, char *map_line, int i, int j);

//+++++++  check_colors.c  +++++++++//

int	check_f_description(t_map *map, char *map_line, int i);
int	check_c_description(t_map *map, char *map_line, int i);

//+++++++++  check_elems.c  ++++++++//

int	check_elems(char **argv, t_map *map);

#endif