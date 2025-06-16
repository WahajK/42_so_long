/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/16 18:59:33 by muhakhan          #+#    #+#             */
/*   Updated: 2025/06/16 19:00:13 by muhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	char_count(char *line, char ch)
{
	int	i;

	i = 0;
	while (*line)
		if (*line++ == ch)
			i++;
	return (i);
}

char	*trim(char *arr)
{
	if (!arr)
		return (NULL);
	if (arr[ft_strlen(arr) - 1] == '\n')
		arr[ft_strlen(arr) - 1] = 0;
	return (arr);
}

int	illegal_char(int row, char *str, t_vars *vars)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '0' || str[i] == '1' || str[i] == 'P'
			|| str[i] == 'E' || str[i] == 'C' || str[i] == 'X')
		{
			if (str[i] == 'P')
			{
				vars->player.x = row;
				vars->player.y = i;
			}
		}
		else
			return (1);
		i++;
	}
	return (0);
}

int	set_counts(t_vars *vars, char *fname)
{
	int		fd;
	char	*str;
	int		flag[2];

	ft_bzero(flag, sizeof(int) * 2);
	fd = open(fname, O_RDONLY);
	if (fd < 0)
		return (1);
	str = trim(get_next_line(fd));
	vars->x_count = ft_strlen(str);
	while (str && ++flag[0])
	{
		if ((int) ft_strlen(str) != vars->x_count
			|| illegal_char(flag[0] - 1, str, vars))
			flag[1] = 1;
		vars->c_count += char_count(str, 'C');
		vars->p_count += char_count(str, 'P');
		vars->e_count += char_count(str, 'E');
		vars->ex_count += char_count(str, 'X');
		free(str);
		str = trim(get_next_line(fd));
	}
	if (!vars->c_count || vars->p_count != 1 || vars->e_count != 1 || flag[1])
		return (close (fd), 1);
	return (vars->y_count = flag[0], close (fd), 0);
}

int	read_map(char *fname, t_vars *vars)
{
	int		fd;
	int		i;
	char	*temp;

	if (set_counts(vars, fname))
		return (1);
	fd = open(fname, O_RDONLY);
	if (fd < 0)
		return (1);
	vars->map = malloc((vars->y_count + 1) * sizeof(char *));
	if (!vars->map)
		return (close(fd), 1);
	temp = get_next_line(fd);
	i = 0;
	while (temp)
	{
		vars->map[i] = trim(temp);
		temp = get_next_line(fd);
		i++;
	}
	vars->map[i] = NULL;
	close(fd);
	return (0);
}