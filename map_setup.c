/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_setup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 17:53:58 by tiade-al          #+#    #+#             */
/*   Updated: 2024/09/22 19:05:33 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

/**@brief This function checks if the map has a viable path reaching the exit 
 * and coins
 * @param argc: The number of arguments passed to the program
 * @param argv: The argument passed to the program
 * @return 0 if the function runs successfully
 */
void	flood_fill(t_d *d, int x, int y)
{
	if (d->map.mtx_copy[y][x] == '1' || d->map.mtx_copy[y][x] == 'F'
		|| d->map.mtx_copy[y][x] == 'X')
	{
		return ;
	}
	else if (d->map.mtx_copy[y][x] == 'C')
	{
		d->assets.coin--;
	}
	else if (d->map.mtx_copy[y][x] == 'E')
	{
		d->map.exit_found = 1;
		return ;
	}
	d->map.mtx_copy[y][x] = 'F';
	flood_fill(d, x + 1, y);
	flood_fill(d, x - 1, y);
	flood_fill(d, x, y + 1);
	flood_fill(d, x, y - 1);
}

/**@brief This function checks if the map is empty or not
 * if it's not it reads all the map so the helped function
 * can start reading from the beginning
 * @param map_name: The name of the map
 * @return void
 */
void	map_x_y_helper(const char *map_name, t_d *d)
{
	int		fd ;
	char	*line;

	fd = open(map_name, O_RDONLY);
	if (!fd || fd == -1)
		error_handler(1, d);
	line = get_next_line(fd);
	if (line == NULL)
	{
		free(line);
		error_handler(5, d);
	}
	while (line != NULL)
	{
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
}

/**@brief This function checks if every line of the map has the same size
 * if all assets are correct, allocates memory for the mtx and the assets(coins
 * and enemies)
 * @param line: One line of the map
 * @param d: The pointer to the d structure
 * @return 0 if the function runs successfully
 */
/* void	map_x_y(const char *map_name, t_d *d)
{
	int		fd ;
	char	*line;
	int		line_size;

	line_size = 0;
	fd = open(map_name, O_RDONLY);
	if (!fd || fd == -1)
		error_handler(1, d);
	line = get_next_line(fd);
	d->map.width = (ft_strlen_to_no(line));
	while (line != NULL)
	{
		line_size = ft_strlen_to_no(line);
		if (line_size != d->map.width)
		{
			free(line);
			close(fd);
			error_handler(2, d);
		}
		d->map.height++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	map_copy(map_name, d);
	assets_counter(d);
	assets_checker(d);
	alloc_c_e_pos(d);
} */

void	map_x_y(const char *map_name, t_d *d)
{
	int		fd;
	char	*line;
	int		line_size;

	fd = open(map_name, O_RDONLY);
	if (fd == -1)
		error_handler(1, d);
	line = get_next_line(fd);
	while (line)
	{
		line_size = ft_strlen_to_no(line);
		check_line_size(line_size, d, line, fd);
		d->map.height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	map_copy(map_name, d);
	assets_counter(d);
	assets_checker(d);
	alloc_c_e_pos(d);
}

void	alloc_c_e_pos(t_d *d)
{
	d->assets.coins_existance = malloc(sizeof(int) * d->assets.coin);
	d->assets.c_pos = malloc(sizeof(t_pos) * d->assets.coin);
	d->assets.enemies_pos = malloc(sizeof(t_pos) * d->assets.enemy);
}

/**@brief This function copies the map to a mtx to be used in the game
 * and a mtx_copy to be used in the flood fill
 * @param map_name: The name of the map
 * @param d: The pointer to the d structure
 * @return 0 if the function runs successfully
 */
int	map_copy(const char *map_name, t_d *d)
{
	int		fd ;
	char	*line;
	int		x;
	int		y;

	y = -1;
	memory_aloc(d);
	fd = open(map_name, O_RDONLY);
	if (!fd || fd == -1)
		error_handler(1, d);
	line = get_next_line(fd);
	while (line && (++y <= d->map.height - 1))
	{
		x = -1;
		while (++x < d->map.width)
		{
			d->map.mtx[y][x] = line[x];
			d->map.mtx_copy[y][x] = line[x];
		}
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	close(fd);
	return (0);
}
