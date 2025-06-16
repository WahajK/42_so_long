/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:20:47 by muhakhan          #+#    #+#             */
/*   Updated: 2025/06/16 18:58:20 by muhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

char	**dup_map(int rc, char **map)
{
	char	**arr;
	int		i;

	arr = malloc(sizeof(char *) * (rc + 1));
	i = 0;
	while (map[i])
	{
		arr[i] = ft_strdup(map[i]);
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

void	solve_maze(char **map, int *flags, int px, int py)
{
	if (map[px][py] == 'V' || map[px][py] == '1')
		return ;
	if (map[px][py] == 'E')
		flags[0] = 1;
	if (map[px][py] == 'C')
		flags[1] = 1;
	map[px][py] = 'V';
	solve_maze(map, flags, px + 1, py);
	solve_maze(map, flags, px - 1, py);
	solve_maze(map, flags, px, py + 1);
	solve_maze(map, flags, px, py - 1);
}

int	check_escape(t_vars *vars)
{
	char	**map_copy;
	int		flags[2];

	ft_bzero(flags, sizeof(int) * 2);
	map_copy = dup_map(vars->y_count, vars->map);
	solve_maze(map_copy, flags, vars->player.x, vars->player.y);
	if (!flags[0] || !flags[1])
		return (destructor_map(map_copy), 1);
	return (destructor_map(map_copy), 0);
}

int	check_borders(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < vars->x_count)
		if (vars->map[0][i++] != '1')
			return (1);
	i = 0;
	while (i < vars->y_count)
		if (vars->map[i++][0] != '1')
			return (1);
	i = 0;
	while (i < vars->y_count)
		if (vars->map[i++][vars->x_count - 1] != '1')
			return (1);
	i = 0;
	while (i < vars->x_count)
		if (vars->map[vars->y_count - 1][i++] != '1')
			return (1);
	return (0);
}

int	validate_map(t_vars *vars)
{
	if (check_borders(vars) || check_escape(vars))
		return (1);
	return (0);
}
