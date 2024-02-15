/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molla <molla@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 08:57:06 by molla             #+#    #+#             */
/*   Updated: 2024/02/15 10:56:55 by molla            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx-linux/mlx.h"
# include "Libft/libft.h"
# include <fcntl.h>
# include <math.h>

typedef struct s_win
{
	void	*mlx_ptr;
	void	*win_ptr;
}	t_win;

typedef struct s_time
{
	double	time;
	double	old_time;
}	t_time;

typedef struct s_img
{
	char	*img_path;
	void	*img_ptr;
	int		img_width;
	int		img_height;
}	t_img;

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
	int		all;
	int		nb_line;
}	t_elems;

typedef struct s_line
{
	int	up;
	int	down;
	int	nb_line_map;
}	t_line;

typedef struct s_map
{
	char	**arr;
	char	player;
	double	posx_init;
	double	posy_init;
	int		nb_line;
	int		map;
}	t_map;

typedef struct s_game
{
	double	posx;
	double	posy;
	double	dirx;
	double	diry;
	double	planx;
	double	plany;
}	t_game;

typedef struct s_cub
{
	t_win	win;
	t_elems	elem;
	t_map	map;
	t_time	time;
	t_game	game;
}	t_cub;

//+++++  check_orientations.c  +++++//

int	check_no_description(t_cub *cub, char *map_line, int i, int j);
int	check_so_description(t_cub *cub, char *map_line, int i, int j);
int	check_we_description(t_cub *cub, char *map_line, int i, int j);
int	check_ea_description(t_cub *cub, char *map_line, int i, int j);

//+++++++  check_colors.c  +++++++++//

int	check_f_description(t_cub *cub, char *map_line, int i);
int	check_c_description(t_cub *cub, char *map_line, int i);

//+++++++++  check_elems.c  ++++++++//

int	check_elems(char **argv, t_cub *cub);

//+++++++  check_map_utils.c  ++++++//

int	check_close(char **arr, t_line *line, int x, int y);
int	create_map_arr(t_cub *cub, int fd, char *argv, int i);

//++++++++++  check_map.c  +++++++++//

int	check_map(t_cub *cub, int fd, char *argv);

//+++++++++++  parsing.c  ++++++++++//

int	parsing(int argc, char **argv, t_cub *cub);

#endif