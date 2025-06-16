/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_images2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:02:31 by muhakhan          #+#    #+#             */
/*   Updated: 2025/06/16 19:02:51 by muhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	destroy_borders(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < 8)
		{
			if (vars->borders.frames[i][j])
				mlx_destroy_image(vars->mlx, vars->borders.frames[i][j]);
			j++;
		}
		i++;
	}
}

void	destroy_images(t_vars *vars)
{
	if (vars->exit.img[0])
		mlx_destroy_image(vars->mlx, vars->exit.img[0]);
	if (vars->exit.img[1])
		mlx_destroy_image(vars->mlx, vars->exit.img[1]);
	free_player_images(vars);
	destroy_borders(vars);
	destroy_obstacle_images(vars);
	destroy_collectible_images(vars);
	if (vars->background)
		mlx_destroy_image(vars->mlx, vars->background);
	if (vars->ex_count != 0)
		destroy_enemy_images(vars);
	if (vars->water)
		mlx_destroy_image(vars->mlx, vars->water);
}

int	destructor(t_vars *vars, char *msg)
{
	ft_printf("%s\n", msg);
	destructor_map(vars->map);
	destroy_images(vars);
	if (vars->window)
		mlx_destroy_window(vars->mlx, vars->window);
	if (vars->mlx)
	{
		mlx_destroy_display(vars->mlx);
		free(vars->mlx);
	}
	free(vars->enemies);
	exit(0);
}