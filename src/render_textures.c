/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:01:35 by muhakhan          #+#    #+#             */
/*   Updated: 2025/06/16 19:21:40 by muhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	continue_border(t_vars *vars)
{
	int	i;

	i = 1;
	while (i < vars->x_count + 1)
	{
		if (i == 1)
			draw_image(vars, vars->borders.frames[5] \
				[vars->borders.frame_index], i++, vars->y_count);
		else if (i == vars->x_count)
			draw_image(vars, vars->borders.frames[7] \
				[vars->borders.frame_index], i++, vars->y_count);
		else
			draw_image(vars, vars->borders.frames[6] \
				[vars->borders.frame_index], i++, vars->y_count);
	}
	i = 2;
	while (i < vars->y_count)
		draw_image(vars, vars->borders.frames[3][vars->borders.frame_index], \
			1, i++);
	i = 2;
	while (i < vars->y_count)
		draw_image(vars, vars->borders.frames[4][vars->borders.frame_index], \
			vars->x_count, i++);
}

void	draw_player(t_vars *vars, int i, int j)
{
	if (vars->player.direction == 0)
		draw_image(vars, vars->player.frames[vars->player.direction] \
			[vars->player.frame_index], j + 1, i + 1);
	else if (vars->player.direction == 1)
		draw_image(vars, vars->player.frames[vars->player.direction] \
			[vars->player.frame_index], j + 1, i + 1);
	else if (vars->player.direction == 2)
		draw_image(vars, vars->player.frames[vars->player.direction] \
			[vars->player.frame_index], j + 1, i + 1);
	else if (vars->player.direction == 3)
		draw_image(vars, vars->player.frames[vars->player.direction] \
			[vars->player.frame_index], j + 1, i + 1);
}

void	draw_enemies(t_vars *vars, int i, int j)
{
	int	k;

	k = 0;
	while (k < vars->ex_count)
	{
		if (vars->enemies[k].x == j && vars->enemies[k].y == i)
		{
			draw_image(vars, vars->enemies[k].frames \
				[vars->enemies[k].direction][vars->enemies[k]. \
				frame_index], j + 1, i + 1);
			break ;
		}
		k++;
	}
}

void	check_and_draw(t_vars *vars, int i, int j)
{
	if (vars->map[i][j] == '1')
		draw_image(vars, vars->obstacle.frames[vars->obstacle.frame_index] \
			, j + 1, i + 1);
	else if (vars->map[i][j] == 'P')
		draw_player(vars, i, j);
	else if (vars->map[i][j] == 'X')
		draw_enemies(vars, i, j);
	else if (vars->map[i][j] == 'E')
		draw_image(vars, vars->exit.img[vars->exit.flag], j + 1, i + 1);
	else if (vars->map[i][j] == 'C')
		draw_image(vars, vars->collectibles.frames[vars->collectibles. \
			frame_index], j + 1, i + 1);
	else
		draw_image(vars, vars->background, j + 1, i + 1);
}

void	render_map(t_vars *vars)
{
	int		i;
	int		j;
	char	*step;

	draw_water(vars);
	draw_border(vars);
	i = 1;
	while (vars->map[i + 1])
	{
		j = 1;
		while (vars->map[i][j + 1])
		{
			check_and_draw(vars, i, j);
			j++;
		}
		i++;
	}
	step = ft_itoa(vars->steps);
	mlx_string_put(vars->mlx, vars->window, 64, 64, 0xFFFFFF, step);
	free(step);
}
