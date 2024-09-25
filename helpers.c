/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helpers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 14:00:46 by tiade-al          #+#    #+#             */
/*   Updated: 2024/09/25 19:03:32 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

/**@brief This function handles the errors
 * @param error_code: The error code
 * @return void
 */
void	error_handler(int error_code, t_d *d)
{
	if (error_code == 1)
	{
		write(1, "Error opening the file descriptor\n", 35);
		exit(1);
	}
	else if (error_code == 2)
	{
		write(1, "Error in the map size!!\n", 24);
		exit(1);
	}
	else if (error_code == 3)
	{
		write(1, "Error, map not winnable\n", 25);
		flood_clean(d);
	}
	else if (error_code == 4)
	{
		write(1, "!!Error!!\nUse [./so_long maps/(map_name).ber]\n", 47);
		exit(1);
	}
	else if (error_code == 5)
	{
		write(1, "Error in the map!!\n", 20);
		exit(1);
	}
}

/**@brief This function counts the amount of ps and exits in the map
 * storing their positions
 * @param d: The pointer to the struct that contains the map
 * @param x: The x position of the p or exit
 * @param y: The y position of the p or exit
 * @param i: The type of asset
 * @return void
 */
void	counter_p_e(t_d *d, int x, int y, int i)
{
	if (i == 1)
	{
		d->assets.p++;
		d->assets.p_pos.x = x;
		d->assets.p_pos.y = y;
	}
	else if (i == 2)
	{
		d->assets.exit++;
		d->assets.exit_pos.x = x;
		d->assets.exit_pos.y = y;
	}
}

void	p_animation_helper(t_d *d, int x, int y, int i)
{
	if (i == d->render.p_frames / 2)
		mlx_put_image_to_window(d->mlx, d->win, d->img.floor, x * 128, y * 128);
	mlx_put_image_to_window(d->mlx, d->win, d->img.p[i],
		d->assets.p_pos.x * 128, d->assets.p_pos.y * 128);
}

void	render_coins_helper(t_d *d, int j, int i)
{
	if (d->assets.c_pos[j].x == d->assets.p_pos.x
		&& d->assets.c_pos[j].y == d->assets.p_pos.y)
		d->assets.coins_existance[j] = 0;
	if (d->assets.coins_existance[j] == 1)
		mlx_put_image_to_window(d->mlx, d->win, d->img.coin[i],
			d->assets.c_pos[j].x * 128, d->assets.c_pos[j].y * 128);
}

/**@brief This function renders the map and updates the counter
 * in the screen
 * @param d: The pointer to the struct that contains the map
 * @return void
 */
int	combined_render(t_d *d)
{
	char	*moves_p;

	d->render.coin_frames = 4;
	mlx_string_put(d->mlx, d->win,
		90, 110, 0xFFFFFF, "MOVES:");
	if (d->map.keycode == 119 || d->map.keycode == 97 || d->map.keycode == 115
		|| d->map.keycode == 100)
	{
		render(d->map.keycode, d);
		mlx_put_image_to_window(d->mlx, d->win, d->img.wall, 128, 0);
		moves_p = ft_itoa(d->counter);
		mlx_string_put(d->mlx, d->win, 145, 110, 0xFFFFFF, moves_p);
		write(1, "Moves: ", 7);
		write(1, moves_p, strlen(moves_p));
		write(1, "\n", 1);
		free (moves_p);
	}
	d->map.keycode = 0;
	render_coins(d);
	render_enemies(d);
	if (d->assets.coin == 0)
		d->map.mtx[d->assets.exit_pos.y][d->assets.exit_pos.x] = 'E';
	return (0);
}
