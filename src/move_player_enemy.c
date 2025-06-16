/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_player_enemy.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 19:05:26 by muhakhan          #+#    #+#             */
/*   Updated: 2025/06/16 19:06:02 by muhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	move_enemies(t_vars *vars)
{
	int		i;
	int		next_x;
	char	next_tile;

	i = 0;
	while (i < vars->ex_count)
	{
		if (vars->enemies[i].direction)
			next_x = vars->enemies[i].x - 1;
		else
			next_x = vars->enemies[i].x + 1;
		next_tile = vars->map[vars->enemies[i].y][next_x];
		if (next_tile == '0' || next_tile == 'P')
		{
			if (next_tile == 'P')
				destructor(vars, "Loser, Loser, Pork Abuser");
			vars->map[vars->enemies[i].y][vars->enemies[i].x] = '0';
			vars->enemies[i].x = next_x;
			vars->map[vars->enemies[i].y][vars->enemies[i].x] = 'X';
		}
		else
			vars->enemies[i].direction = !vars->enemies[i].direction;
		i++;
	}
}

void	init_enemies(t_vars *vars)
{
	int	i;
	int	j;
	int	count;

	vars->enemies = malloc(vars->ex_count * sizeof(t_enemy));
	i = 0;
	count = 0;
	while (vars->map[i])
	{
		j = 0;
		while (vars->map[i][j])
		{
			if (vars->map[i][j] == 'X')
			{
				vars->enemies[count].x = j;
				vars->enemies[count].y = i;
				vars->enemies[count].direction = 0;
				vars->enemies[count].frame_index = 0;
				set_enemy_frames(vars, count);
				count++;
			}
			j++;
		}
		i++;
	}
}

void	move_player(t_vars *vars, int x, int y)
{
	ft_printf("Steps: %d\n", vars->steps);
	if (vars->map[vars->player.x + x][vars->player.y + y] == '1')
		return ;
	if (vars->map[vars->player.x + x][vars->player.y + y] == 'X')
		destructor(vars, "Loser, Loser, Pork Abuser");
	if (vars->map[vars->player.x + x][vars->player.y + y] == 'E')
	{
		if (vars->c_count == 0)
			destructor(vars, "Winner, Winner, Chicken Dinner");
		else
			return ;
	}
	if (vars->map[vars->player.x + x][vars->player.y + y] == 'C')
		vars->c_count--;
	vars->map[vars->player.x][vars->player.y] = '0';
	vars->map[vars->player.x + x][vars->player.y + y] = 'P';
	vars->player.x = vars->player.x + x;
	vars->player.y = vars->player.y + y;
	render_map(vars);
}