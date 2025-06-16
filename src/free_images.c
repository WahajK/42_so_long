/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_images.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:00:29 by muhakhan          #+#    #+#             */
/*   Updated: 2025/06/16 19:00:59 by muhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	destructor_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
		free(map[i++]);
	free(map);
}

void	destroy_enemy_images(t_vars *var)
{
	int	i;
	int	j;

	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < 7)
		{
			if (var->en_frames[i][j])
				mlx_destroy_image(var->mlx, var->en_frames[i][j]);
			j++;
		}
		i++;
	}
}

void	destroy_collectible_images(t_vars *var)
{
	int	i;

	i = 0;
	while (i < 7)
	{
		if (var->collectibles.frames[i])
			mlx_destroy_image(var->mlx, var->collectibles.frames[i]);
		i++;
	}
}

void	free_player_images(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < 6)
		{
			if (vars->player.frames[i][j])
				mlx_destroy_image(vars->mlx, vars->player.frames[i][j]);
			j++;
		}
		i++;
	}
}

void	destroy_obstacle_images(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < 8)
	{
		if (vars->obstacle.frames[i])
			mlx_destroy_image(vars->mlx, vars->obstacle.frames[i]);
		i++;
	}
}
