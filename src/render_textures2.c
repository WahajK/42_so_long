/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textures2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:03:10 by muhakhan          #+#    #+#             */
/*   Updated: 2025/06/16 19:03:37 by muhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	check_obstacles_player(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < 8)
		if (!vars->obstacle.frames[i++])
			destructor(vars, "Missing Textures!");
	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < 6)
			if (!vars->player.frames[i][j++])
				destructor(vars, "Missing Textures!");
		i++;
	}
	i = 0;
	while (i < 7)
		if (!vars->collectibles.frames[i++])
			destructor(vars, "Missing Textures!");
	if (!vars->background || !vars->water || !vars->exit.img[0] \
		|| !vars->exit.img[1])
		destructor(vars, "Missing Textures!");
}

void	check_missing_textures(t_vars *vars)
{
	int	i;
	int	j;

	check_obstacles_player(vars);
	i = 0;
	while (i < 8)
	{
		j = 0;
		while (j < 8)
			if (!vars->borders.frames[i][j++])
				destructor(vars, "Missing Textures!");
		i++;
	}
	i = 0;
	if (vars->ex_count != 0)
	{
		while (i < 2)
		{
			j = 0;
			while (j < 7)
				if (!vars->en_frames[i][j++])
					destructor(vars, "Missing Textures!");
			i++;
		}
	}
}

void	draw_image(t_vars *vars, void *img, int x, int y)
{
	mlx_put_image_to_window(vars->mlx, vars->window, \
		img, TILE_SIZE * x, TILE_SIZE * y);
}

void	draw_water(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->x_count + 2)
		draw_image(vars, vars->water, i++, 0);
	i = 0;
	while (i < vars->y_count + 2)
		draw_image(vars, vars->water, 0, i++);
	i = 0;
	while (i < vars->x_count + 2)
		draw_image(vars, vars->water, i++, vars->y_count + 1);
	i = 0;
	while (i < vars->y_count + 2)
		draw_image(vars, vars->water, vars->x_count + 1, i++);
}

void	draw_border(t_vars *vars)
{
	int	i;

	i = 1;
	while (i < vars->x_count + 1)
	{
		if (i == 1)
			draw_image(vars, vars->borders.frames[0] \
				[vars->borders.frame_index], i++, 1);
		else if (i == vars->x_count)
			draw_image(vars, vars->borders.frames[2] \
				[vars->borders.frame_index], i++, 1);
		else
			draw_image(vars, vars->borders.frames[1] \
				[vars->borders.frame_index], i++, 1);
	}
	continue_border(vars);
}
