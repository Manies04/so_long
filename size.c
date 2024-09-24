/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   size.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tiade-al <tiade-al@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 19:05:23 by tiade-al          #+#    #+#             */
/*   Updated: 2024/09/22 19:08:30 by tiade-al         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/so_long.h"

void	check_line_size(int line_size, t_d *d, char *line, int fd)
{
	if (!d->map.width)
		d->map.width = line_size;
	else if (line_size != d->map.width)
	{
		free(line);
		close(fd);
		error_handler(2, d);
	}
}
