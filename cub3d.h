/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: molla <molla@student.42nice.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/08 08:57:06 by molla             #+#    #+#             */
/*   Updated: 2024/03/01 10:27:37 by molla            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "minilibx-linux/mlx.h"
# include "Libft/libft.h"
# include <fcntl.h>
# include <math.h>

# define W 119
# define S 115
# define A 97
# define D 100
# define RIGHT 65361
# define LEFT 65363
# define ESCAPE 65307

typedef struct s_img
{
	void	*mlx_img;
	char	*addr;
	int		bpp; /* bits per pixel */
	int		line_len;
	int		endian;
	int		x;
	int		y;
}	t_img;

typedef struct s_win
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		height;
	int		width;
	t_img	img;
}	t_win;

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
	int		f_color;
	int		c_color;
	double	posx;
	double	posy;
	int		mapx;
	int		mapy;
	double	dirx;
	double	diry;
	double	planx;
	double	plany;
	double	camerax;
	double	raydirx;
	double	raydiry;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	stepx;
	double	stepy;
	int		hit;
	int		side;
	double	perpwalldist;
	int		lineheight;
	int		drawstart;
	int		drawend;
	t_img	wall_no;
	t_img	wall_so;
	t_img	wall_we;
	t_img	wall_ea;
	int		*size;
	double	wallx;
	int		texx;
	int		texy;
	double	step;
	double	texpos;
}	t_game;

typedef struct s_cub
{
	t_win	win;
	t_elems	elem;
	t_map	map;
	t_game	game;
}	t_cub;

//+++++  check_orientations.c  +++++//

int				check_no_description(t_cub *cub, char *map_line, int i, int j);
int				check_so_description(t_cub *cub, char *map_line, int i, int j);
int				check_we_description(t_cub *cub, char *map_line, int i, int j);
int				check_ea_description(t_cub *cub, char *map_line, int i, int j);

//+++++++  check_colors.c  +++++++++//

int				check_f_description(t_cub *cub, char *map_line, int i);
int				check_c_description(t_cub *cub, char *map_line, int i);

//+++++++++  check_elems.c  ++++++++//

int				check_elems(char **argv, t_cub *cub);

//+++++++  check_map_utils.c  ++++++//

int				check_close(char **arr, t_line *line, int x, int y);
int				create_map_arr(t_cub *cub, int fd, char *argv);

//++++++++++  check_map.c  +++++++++//

int				check_map(t_cub *cub, int fd, char *argv);

//+++++++++++  parsing.c  ++++++++++//

int				parsing(int argc, char **argv, t_cub *cub);

//++++++++++++  init.c  ++++++++++++//

void			init_game(t_cub *cub);
void			init_player_orientation(t_cub *cub);
void			calculs_init(t_cub *cub, int x);

//+++++++++++  render.c  +++++++++++//

void			exit_cub(t_cub *cub);
int				render(t_cub *cub);
int				close_window(int keycode, void *param);
int				keypress(int keycode, t_cub *cub);

//+++++++++++  calculs.c  ++++++++++//

void			calculate_deltas(t_cub *cub);
void			calculate_step_and_sidedist(t_cub *cub);
void			dda_algo(t_cub *cub);

//+++++++++++  drawing.c  ++++++++++//

int				convert_to_color(int color[3]);
void			establishement_draw(t_cub *cub);
unsigned int	get_pixel_color(t_img img, int x, int y);
void			my_pixel_put(t_cub *cub, int x, int y, int color);
void			draw_verline(t_cub *cub, int x);//, int color);

//++++++++++  movements.c  +++++++++//

void			forward_mvt(t_cub *cub);
void			backward_mvt(t_cub *cub);
void			leftside_mvt(t_cub *cub);
void			rightside_mvt(t_cub *cub);

//++++++++++  rotations.c  +++++++++//

void			left_rot(t_cub *cub);
void			right_rot(t_cub *cub);

//++++++++++  textures.c  ++++++++++//

int				init_texture(t_cub *cub);
void			establishment_textures(t_cub *cub);
t_img			find_texture(t_cub *cub);

#endif