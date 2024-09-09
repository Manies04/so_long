/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:46:48 by tiade-al          #+#    #+#             */
/*   Updated: 2024/08/04 16:42:21 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

/**@brief This animates the p movement
 * @param d: The pointer to the struct that contains the map
 * @param x: The x position of the p
 * @param y: The y position of the p
 * @param i: The index of the p frame(starts at 0)
 * @return void
 */
void	p_animation(t_d *d, int x, int y, int i)
{
	float	total_elapsed_time;

	total_elapsed_time = 0;
	while (i < d->render.p_frames)
	{
		total_elapsed_time += (update_delta_time());
		if (total_elapsed_time >= d->render.frame_time_p)
		{
			if (i < d->render.p_frames / 2)
				mlx_put_image_to_window(d->mlx, d->win, d->img.p[i],
					x * 128, y * 128);
			else
				p_animation_helper(d, x, y, i);
			mlx_do_sync(d->mlx);
			total_elapsed_time = 0;
			i++;
		}
	}
	d->counter++;
	if (d->assets.coin == 0)
		mlx_put_image_to_window(d->mlx, d->win, d->img.exit,
			d->assets.exit_pos.x * 128, d->assets.exit_pos.y * 128);
}

/**@brief This function moves the p in the map if he hasn't collided with a wall
 * updating the map matrix, else it stays in the same position
 * @param keycode: The keycode of the key pressed
 * @param d: The pointer to the struct that contains the map
 * @return void
 */
void	render(int keycode, t_d *d)
{
	int	x;
	int	y;

	x = d->assets.p_pos.x;
	y = d->assets.p_pos.y;
	if (keycode == 119)
		d->assets.p_pos.y--;
	else if (keycode == 97)
		d->assets.p_pos.x--;
	else if (keycode == 115)
		d->assets.p_pos.y++;
	else if (keycode == 100)
		d->assets.p_pos.x++;
	if (colision_checker(d) == 0)
	{
		d->map.mtx[d->assets.p_pos.y][d->assets.p_pos.x] = 'P';
		d->map.mtx[y][x] = '0';
		p_animation(d, x, y, 0);
	}
	else
	{
		d->assets.p_pos.x = x;
		d->assets.p_pos.y = y;
	}
}

/**@brief This function renders the coins in the map
 * @param d: The pointer to the struct that contains the map
 * @return void
 */
void	render_coins(t_d *d)
{
	int		i;
	float	total_elapsed_time;
	int		j;

	i = 0;
	total_elapsed_time = 0;
	while (i < d->render.coin_frames)
	{
		d->map.delta_time_coins = (update_delta_time());
		total_elapsed_time += d->map.delta_time_coins;
		if (total_elapsed_time >= d->render.frame_time_c_e)
		{
			j = -1;
			while (++j < d->assets.stable_coins)
				render_coins_helper(d, j, i);
			mlx_do_sync(d->mlx);
			total_elapsed_time = 0;
			i++;
		}
	}
}

/**@brief This function renders the enemies in the map
 * @param d: The pointer to the struct that contains the map
 * @return void
 */
void	render_enemies(t_d *d)
{
	int		i;
	float	total_elapsed_time;
	int		j;

	i = 0;
	total_elapsed_time = 0;
	while (i < d->render.enemy_frames)
	{
		d->map.delta_time_enemies = (update_delta_time());
		total_elapsed_time += d->map.delta_time_enemies;
		if (total_elapsed_time >= d->render.frame_time_c_e)
		{
			j = 0;
			while (j < d->assets.enemy)
			{
				mlx_put_image_to_window(d->mlx, d->win, d->img.enemy[i],
					d->assets.enemies_pos[j].x * 128,
					d->assets.enemies_pos[j].y * 128);
				j++;
			}
			mlx_do_sync(d->mlx);
			total_elapsed_time = 0;
			i++;
		}
	}
}

/**@brief This function updates the delta time
 * @param d: The pointer to the struct that contains the map
 * @return The delta time
 */
float	update_delta_time(void)
{
	static struct timeval	last_time;
	struct timeval			current_time;
	float					delta_time;

	gettimeofday(&current_time, NULL);
	(delta_time) = (current_time.tv_sec - last_time.tv_sec)
		+(current_time.tv_usec - last_time.tv_usec) / 1000000.0;
	last_time = current_time;
	return (delta_time);
}
