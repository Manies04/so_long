/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 18:10:50 by tiade-al          #+#    #+#             */
/*   Updated: 2024/09/24 16:17:36 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

/**@brief This function checks if the argument is valid and the amount of args
 * @param argc: The number of arguments passed to the program
 * @param argv: The argument passed to the program
 * @return 0 if the function runs successfully
 */
void	arg_checker(int argc, t_d *d)
{
	int		i;
	char	*argv;

	argv = d->map.name;
	i = ft_strlen(argv);
	i--;

	if (ft_strlen(argv) < 5 || argc < 2 || argc > 2)
		error_handler(4, d);
	else if (i >= 4 && (argv[i] != 'r'
			|| argv[i - 1] != 'e'
			|| argv[i - 2] != 'b'
			|| argv[i - 3] != '.'))
	{
		write(1, "You must use a .ber file!!\n", 28);
		exit(1);
	}
}

/**@brief This function checks if there is a p, an exit and at least 
 * one coin in the map
 * @param d: The pointer to the struct that contains the map
 * @return 0 if the function runs successfully
 */
void	assets_checker(t_d *d)
{
	int	i;

	i = 0;
	if (d->assets.p != 1
		|| d->assets.exit != 1
		|| d->assets.coin < 1
		|| d->map.height % d->map.width == 0)
	{
		write(1, "Error in the amount of assets!!\n", 33);
		write(1, "You need at least one p, one exit and one coin!!\n", 50);
		while (i < d->map.height)
		{
			free(d->map.mtx[i]);
			free(d->map.mtx_copy[i]);
			i++;
		}
		free(d->map.mtx);
		free(d->map.mtx_copy);
		exit(1);
	}
}

/**@brief This function counts the amount assets in the map
 * and saves the position of the p and the exit
 * @param line: The line of the map
 * @param d: The pointer to the struct that contains the map
 * @return 0 if the function runs successfully
 */
void	assets_counter(t_d *d)
{
	int	x;
	int	y;

	y = 0;
	while (y < (d->map.height))
	{
		x = 0;
		while (x < (d->map.width))
		{
			if (d->map.mtx[y][x] == 'P')
				counter_p_e(d, x, y, 1);
			else if (d->map.mtx[y][x] == 'E')
				counter_p_e(d, x, y, 2);
			else if (d->map.mtx[y][x] == 'C')
				d->assets.coin++;
			else if (d->map.mtx[y][x] == 'X')
				d->assets.enemy++;
			else if (d->map.mtx[y][x] != '1' && d->map.mtx[y][x] != '0')
				error_handler(5, d);
			x++;
		}
		y++;
	}
	d->assets.stable_coins = d->assets.coin;
}

/**@brief This function checks where the p is going to move and if it is a 
 * valid move
 * @param d: The pointer to the struct that contains the map
 * @return 0 if the function runs successfully
 */
int	colision_checker(t_d *d)
{
	if (d->map.mtx[d->assets.p_pos.y][d->assets.p_pos.x] == '1')
	{
		write(1, "You might get a concussion ", 28);
		write(1, "if you hit the wall hard enough!!\n", 35);
		return (1);
	}
	else if (d->map.mtx[d->assets.p_pos.y][d->assets.p_pos.x] == 'X')
	{
		write(1, "You Lost!!\n", 11);
		exit (1);
	}
	else if (d->map.mtx[d->assets.p_pos.y][d->assets.p_pos.x] == 'C')
	{
		d->map.mtx[d->assets.p_pos.y][d->assets.p_pos.x] = '0';
		d->assets.coin--;
		return (0);
	}
	else if (d->map.mtx[d->assets.p_pos.y][d->assets.p_pos.x] == 'E'
			&& d->assets.coin <= 0)
	{
		write(1, "You Won!!\n", 10);
		exit (1);
	}
	else
		return (0);
}

/**@brief This function checks if the map has bounderies '1'
 * @param d: The pointer to the struct that contains the map
 * @return 0 if the function runs successfully
 */
int	bounderies_checker(t_d *d)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (x < d->map.width)
	{
		if (d->map.mtx[0][x] != '1'
			|| d->map.mtx[d->map.height - 1][x] != '1')
			error_handler(5, d);
		x++;
	}
	while (y < d->map.height)
	{
		if (d->map.mtx[y][0] != '1'
			|| d->map.mtx[y][d->map.width - 1] != '1')
			error_handler(5, d);
		y++;
	}
	return (0);
}
