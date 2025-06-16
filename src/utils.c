/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:10:24 by muhakhan          #+#    #+#             */
/*   Updated: 2025/06/16 19:10:47 by muhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	check_extension(char *fname)
{
	if (ft_strncmp(&fname[ft_strlen(fname) - 4], ".ber", 4) != 0)
		return (1);
	return (0);
}

void	start_game_window(t_vars *vars)
{
	int	size_x;
	int	size_y;

	vars->mlx = mlx_init();
	if (!vars->mlx)
		destructor(vars, "Failed to initialize MLX");
	mlx_get_screen_size(vars->mlx, &size_x, &size_y);
	if ((vars->x_count + 2) * TILE_SIZE > size_x
		|| (vars->y_count + 2) * TILE_SIZE > size_y)
		destructor(vars, "Map too big for screen");
	vars->window = mlx_new_window(vars->mlx, (vars->x_count + 2) * TILE_SIZE \
		, (vars->y_count + 2) * TILE_SIZE, "Meow");
	if (!vars->window)
		destructor(vars, "Failed to initialize Window");
}

int	handle_exit(t_vars *vars)
{
	destructor(vars, "You pressed the red button?");
	return (0);
}
