/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/04 01:27:15 by tiade-al          #+#    #+#             */
/*   Updated: 2024/09/18 15:00:10 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

/**@brief This function reads the .ber file and creates the background of the 
 * game setting the counters of coins and enemies to 0 after the memory was 
 * allocated so they can be counted later
*@param map_name: The name of the .ber file
*@param d: The pointer to the d structure
*@return 0 if the function runs successfully
*/
void	background(t_d *d)
{
	d->assets.enemy = 0;
	d->assets.coin = 0;
	add_to_map(d);
	bounderies_checker(d);
}

/**@brief This function translates the elements of the map to the window
 *  keeping the positions of coins and enemies
 * @param line: One line of the map
 * @param d: The pointer to the d structure
 * @return 0 if the function runs successfully
 */
void	add_to_map( t_d *d)
{
	int	x;
	int	y;

	y = -1;
	while (++y < d->map.height)
	{
		x = 0;
		while (x < d->map.width)
		{
			if (d->map.mtx[y][x] == '1')
				mlx_put_image_to_window(d->mlx, d->win,
					d->img.wall, x * 128, y * 128);
			if (d->map.mtx[y][x] == '0' || d->map.mtx[y][x] == 'E')
				mlx_put_image_to_window(d->mlx, d->win,
					d->img.floor, x * 128, y * 128);
			if (d->map.mtx[y][x] == 'P')
				mlx_put_image_to_window(d->mlx, d->win,
					d->img.p[6], x * 128, y * 128);
			if (d->map.mtx[y][x] == 'C')
				initiator(d, x, y, 0);
			if (d->map.mtx[y][x] == 'X')
				initiator(d, x, y, 1);
			x++;
		}
	}
}

void	initiator(t_d *d, int x, int y, int i)
{
	if (i == 0)
	{
		d->assets.c_pos[d->assets.coin] = (t_pos){x, y};
		d->assets.coins_existance[d->assets.coin] = 1;
		d->assets.coin++;
	}
	else if (i == 1)
	{
		d->assets.enemies_pos[d->assets.enemy++] = (t_pos){x, y};
		mlx_put_image_to_window(d->mlx, d->win,
			d->img.enemy[0], x * 128, y * 128);
	}
}

void	free_all(t_d *d)
{
	int	i;

	i = 0;
	free(d->assets.coins_existance);
	free(d->assets.c_pos);
	free(d->assets.enemies_pos);
	mlx_destroy_image(d->mlx, d->img.wall);
	mlx_destroy_image(d->mlx, d->img.floor);
	mlx_destroy_image(d->mlx, d->img.exit);
	while (i < 7)
		mlx_destroy_image(d->mlx, d->img.p[i++]);
	mlx_destroy_image(d->mlx, d->img.enemy[0]);
	mlx_destroy_image(d->mlx, d->img.enemy[1]);
	mlx_destroy_image(d->mlx, d->img.coin[0]);
	mlx_destroy_image(d->mlx, d->img.coin[1]);
	mlx_destroy_image(d->mlx, d->img.coin[2]);
	mlx_destroy_image(d->mlx, d->img.coin[3]);
	mlx_destroy_window(d->mlx, d->win);
	clean_matrix(d);
	mlx_destroy_display(d->mlx);
	free(d->mlx);
	exit(0);
}

void	clean_matrix(t_d *d)
{
	int	i;

	i = 0;
	while (i < d->map.height)
	{
		free(d->map.mtx[i]);
		free(d->map.mtx_copy[i]);
		i++;
	}
	free(d->map.mtx);
	free(d->map.mtx_copy);
}
