/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/21 11:26:47 by tiade-al          #+#    #+#             */
/*   Updated: 2024/09/25 19:14:21 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

int	main(int argc, char **argv)
{
	t_d	d;
	int	coins;
	int	enemys;

	struct_init(&d);
	d.map.name = argv[1];
	if (argc < 2)
		d.map.name = "";
	arg_checker(argc, &d);
	map_x_y_helper(argv[1], &d);
	map_x_y(argv[1], &d);
	coins = d.assets.coin;
	enemys = d.assets.enemy;
	flood_fill(&d, d.assets.p_pos.x, d.assets.p_pos.y);
	if (d.assets.coin != 0 || d.map.exit_found != 1)
		error_handler(3, &d);
	d.assets.coin = coins;
	d.assets.enemy = enemys;
	initializer(&d);
	background(&d);
	mlx_loop_hook(d.mlx, combined_render, &d);
	mlx_hook(d.win, 2, 1L << 0, key_press, &d);
	mlx_hook(d.win, 17, 0, close_window, &d);
	mlx_loop(d.mlx);
	return (free_all(&d), 0);
}
