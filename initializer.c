/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 13:46:41 by tiade-al          #+#    #+#             */
/*   Updated: 2024/09/24 12:57:49 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

/**@brief This function initializes the mlx window and the images
 * @param d: The pointer to the struct that contains the map
 * @return void
 */
void	initializer(t_d *d)
{
	int	window_width;
	int	window_height;

	window_width =  d->map.width * 128;
	window_height = d->map.height * 128;
	d->mlx = mlx_init();
	d->win = mlx_new_window(d->mlx, window_width, window_height, "So_long");
	d->img.wall = mlx_xpm_file_to_image(d->mlx, "textures/Wall.xpm",
			&d->width, &d->height);
	d->img.floor = mlx_xpm_file_to_image(d->mlx, "textures/Floor.xpm",
			&d->width, &d->height);
	image_p(d);
	image_enemy(d);
	image_coins(d);
	d->img.exit = mlx_xpm_file_to_image(d->mlx, "textures/Exit.xpm",
			&d->width, &d->height);
}

void	struct_init(t_d *d)
{
	ft_memset(d, 0, sizeof(t_d));
	d->counter = 0;
	d->map.height = 0;
	d->map.width = 0;
	d->assets.p = 0;
	d->assets.exit = 0;
	d->assets.coin = 0;
	d->assets.enemy = 0;
	d->render.coin_frames = 4;
	d->render.enemy_frames = 2;
	d->render.p_frames = 7;
	d->render.frame_time_c_e = 0.1;
	d->render.frame_time_p = 0.035;
	d->map.exit_found = 0;
	d->map.keycode = 0;
}

// Callback function for key press events
/**@brief This function handles the key press events for (WASD) and the ESC key
 * @param keycode: The keycode of the key pressed
 * @param d: The pointer to the struct that contains the map
 * @return 0 if the function runs successfully
 */
int	key_press(int keycode, t_d *d)
{
	if (keycode == 65307)
	{
		free_all(d);
		exit(0);
	}
	if (keycode == 119 || keycode == 97 || keycode == 115 || keycode == 100)
		d->map.keycode = keycode;
	else
		write(1, "W A S D only\nEsc to exit\n", 26);
	return (0);
}

/**@brief This function closes the window
 * @param param: The pointer to the struct that contains the map
 * @return 0 if the function runs successfully
 */
int	close_window(t_d *d)
{
	free_all(d);
	exit(0);
	return (0);
}
