/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/20 18:37:17 by tiade-al          #+#    #+#             */
/*   Updated: 2024/09/25 18:56:21 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# include "get_next_line.h"
# include "../Libft/libft.h"
# include "../minilibx-linux/mlx.h"
# include <stdlib.h>
# include <stdio.h>
# include <stdbool.h> 
# include <sys/time.h>
# include <unistd.h>

typedef struct s_render
{
	int		coin_frames;
	int		enemy_frames;
	int		p_frames;
	float	frame_time_c_e;
	float	frame_time_p;
}		t_render;

typedef struct s_position
{
	int	x;
	int	y;
}		t_pos;

typedef struct s_assets
{
	int		p;//how many in game
	t_pos	p_pos;//x,y position
	int		enemy;//how many in game
	t_pos	*enemies_pos;//x,y position
	int		coin;//how many in game, decremented when p passes by
	int		stable_coins;//stable amount of coins for loop
	t_pos	*c_pos;//x,y position
	int		*coins_existance;//render coins
	int		exit;//how many in game
	t_pos	exit_pos;//x,y position
}		t_assets;

typedef struct s_map
{
	char	**mtx;//map in mtx form
	char	**mtx_copy;//map in mtx form for flood fill
	int		width;//to load the window
	int		height;//to load the window
	char	*name;//argv[1]
	int		exit_found;
	float	delta_time_coins;
	float	delta_time_enemies;
	int		keycode;
}		t_map;

typedef struct s_img
{
	void	*wall;
	void	*floor;
	void	*p[7];
	void	*enemy[2];
	void	*coin[4];
	void	*exit;
}		t_img;

typedef struct s_d
{
	void		*mlx;//initialization
	void		*win;//initialization
	int			width;//initiate the img
	int			height;//initiate img
	int			counter;//move counter
	t_map		map;
	t_img		img;
	t_assets	assets;
	t_render	render;
}		t_d;

//background.c
void	background(t_d *d);
void	add_to_map( t_d *d);
void	initiator(t_d *d, int x, int y, int i);
void	free_all(t_d *d);
void	clean_matrix(t_d *d);

//checkers.c
void	arg_checker(int argc, t_d *d);
void	assets_checker(t_d *d);
void	assets_counter(t_d *d);
int		colision_checker(t_d *d);
int		bounderies_checker(t_d *d);

//helpers.c
void	error_handler(int error_code, t_d *d);
void	counter_p_e(t_d *d, int x, int y, int i);
void	p_animation_helper(t_d *d, int x, int y, int i);
void	render_coins_helper(t_d *d, int j, int i);
int		combined_render(t_d *d);

//map_setup.c
void	flood_fill(t_d *d, int x, int y);
void	map_x_y_helper(const char *map_name, t_d *d);
void	map_x_y(const char *map_name, t_d *d);
int		map_copy(const char *map_name, t_d *d);
void	alloc_c_e_pos(t_d *d);

//img_resizer.c
size_t	ft_strlen_to_no(const char *str);
void	memory_aloc(t_d *d);
void	image_coins(t_d *d);
void	image_p(t_d *d);
void	image_enemy(t_d *d);

//initializer.c
void	initializer(t_d *d);
void	struct_init(t_d *d);
int		key_press(int keycode, t_d *d);
int		close_window(t_d *d);

//animation.c
void	p_animation(t_d *d, int x, int y, int i);
void	render(int keycode, t_d *d);
void	render_coins(t_d *d);
void	render_enemies(t_d *d);
float	update_delta_time(void);

//size.c
void	check_line_size(int line_size, t_d *d, char *line, int fd);
void	flood_clean(t_d *d);

#endif