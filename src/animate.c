/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animate.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:04:23 by muhakhan          #+#    #+#             */
/*   Updated: 2025/06/16 19:21:49 by muhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	handle_key(int keysym, t_vars *vars)
{
	if (keysym == XK_w)
	{
		vars->steps++;
		move_player(vars, -1, 0);
	}
	if (keysym == XK_s)
	{
		vars->steps++;
		move_player(vars, 1, 0);
	}
	if (keysym == XK_a)
	{
		vars->steps++;
		vars->player.direction = 1;
		move_player(vars, 0, -1);
	}
	if (keysym == XK_d)
	{
		vars->steps++;
		vars->player.direction = 0;
		move_player(vars, 0, 1);
	}
	if (keysym == XK_Escape)
		destructor(vars, "You Pressed Escape?");
	return (0);
}

void	animate_collectible(t_vars *vars, int frame)
{
	if (frame % 300 == 0 && !vars->collectibles.flag)
	{
		vars->collectibles.frame_index++;
		if (vars->collectibles.frame_index >= 7)
		{
			vars->collectibles.frame_index = 6;
			vars->collectibles.flag = 1;
		}
	}
}

void	animate_player_obs(t_vars *vars, int frame)
{
	int	i;

	if (frame % 300 == 0)
	{
		i = 0;
		while (i < vars->ex_count)
		{
			vars->enemies[i].frame_index++;
			if (vars->enemies[i].frame_index >= 7)
				vars->enemies[i].frame_index = 0;
			i++;
		}
		vars->player.frame_index++;
		vars->obstacle.frame_index++;
		vars->borders.frame_index++;
		if (vars->borders.frame_index >= 8)
			vars->borders.frame_index = 0;
		if (vars->obstacle.frame_index >= 8)
			vars->obstacle.frame_index = 0;
		if (vars->player.frame_index >= 6)
			vars->player.frame_index = 0;
	}
}

int	update_game(t_vars *vars)
{
	static int	frame = 0;

	frame++;
	animate_collectible(vars, frame);
	animate_player_obs(vars, frame);
	if (frame % 2000 == 0)
		move_enemies(vars);
	if (frame % 30 == 0)
	{
		if (vars->c_count == 0)
			vars->exit.flag = 1;
		render_map(vars);
	}
	return (0);
}
