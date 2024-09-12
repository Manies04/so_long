/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_resizer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/10 13:05:00 by tiade-al          #+#    #+#             */
/*   Updated: 2024/09/11 23:39:36 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

/**brief This function gets the size of the string until the first '\n' or '\0'
 * @param str: The string to be checked
 * @return 0 if the function runs successfully
 */
size_t	ft_strlen_to_no(const char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	return (i);
}

/**@brief This function allocates memory for the mtx and mtx_copy
 * @param d: The pointer to the d structure
 * @return void
 */
void	memory_aloc(t_d *d)
{
	int	i;

	i = 0;
	d->map.mtx = (char **)malloc(sizeof(char *) * d->map.height);
	d->map.mtx_copy = (char **)malloc(sizeof(char *) * d->map.height);
	while (i < d->map.height)
	{
		d->map.mtx[i] = (char *)ft_calloc(d->map.width, sizeof(char));
		d->map.mtx_copy[i] = (char *)ft_calloc(d->map.width, sizeof(char));
		i++;
	}
}

void	image_coins(t_d *d)
{
	d->img.coin[0] = mlx_xpm_file_to_image(d->mlx,
			"textures/Coin_face.xpm", &d->width, &d->height);
	d->img.coin[1] = mlx_xpm_file_to_image(d->mlx,
			"textures/Coin_side.xpm", &d->width, &d->height);
	d->img.coin[2] = mlx_xpm_file_to_image(d->mlx,
			"textures/Coin_D.xpm", &d->width, &d->height);
	d->img.coin[3] = mlx_xpm_file_to_image(d->mlx,
			"textures/Coin_side.xpm", &d->width, &d->height);
}

void	image_p(t_d *d)
{
	d->img.p[0] = mlx_xpm_file_to_image(d->mlx,
			"textures/P1.xpm", &d->width, &d->height);
	d->img.p[1] = mlx_xpm_file_to_image(d->mlx,
			"textures/P2.xpm", &d->width, &d->height);
	d->img.p[2] = mlx_xpm_file_to_image(d->mlx,
			"textures/P3.xpm", &d->width, &d->height);
	d->img.p[3] = mlx_xpm_file_to_image(d->mlx,
			"textures/P4.xpm", &d->width, &d->height);
	d->img.p[4] = mlx_xpm_file_to_image(d->mlx,
			"textures/P5.xpm", &d->width, &d->height);
	d->img.p[5] = mlx_xpm_file_to_image(d->mlx,
			"textures/P6.xpm", &d->width, &d->height);
	d->img.p[6] = mlx_xpm_file_to_image(d->mlx,
			"textures/P0_still.xpm", &d->width, &d->height);
}

void	image_enemy(t_d *d)
{
	d->img.enemy[0] = mlx_xpm_file_to_image(d->mlx,
			"textures/Enemy1.xpm", &d->width, &d->height);
	d->img.enemy[1] = mlx_xpm_file_to_image(d->mlx,
			"textures/Enemy2.xpm", &d->width, &d->height);
}
