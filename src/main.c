/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:52:20 by muhakhan          #+#    #+#             */
/*   Updated: 2025/05/25 20:11:50 by muhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	check_extension(char *fname)
{
	if (ft_strncmp(&fname[ft_strlen(fname) - 4], ".ber", 4) != 0)
		return (1);
	return (0);
}

int	get_row_count(char *fname)
{
	int		fd;
	int		i;
	char	*str;

	i = 0;
	fd = open(fname, O_RDONLY);
	if (fd < 0)
		return (1);
	str = get_next_line(fd);
	while (str)
	{
		free(str);
		str = get_next_line(fd);
		i++;
	}
	close(fd);
	return (i);
}

char	*trim(char *arr)
{
	if (arr[ft_strlen(arr) - 1] == '\n')
		arr[ft_strlen(arr) - 1] = 0;
	return (arr);
}

int	read_map(char *fname, t_map *map)
{
	int		fd;
	int		i;
	char	*temp;

	fd = open(fname, O_RDONLY);
	if (fd < 0)
		return (1);
	map->row_count = get_row_count(fname);
	if (!map->row_count)
		return (1);
	map->map = malloc((map->row_count + 1) * sizeof(char *));
	if (!map->map)
		return (1);
	temp = get_next_line(fd);
	i = 0;
	while (temp)
	{
		map->map[i++] = trim(temp);
		temp = get_next_line(fd);
	}
	map->map[i] = NULL;
	close(fd);
	return (0);
}

void	print_map(t_map *map)
{
	int	i;

	i = 0;
	while (map->map[i])
	{
		ft_printf("%s\n", map->map[i++]);
	}
}

int	check_escape(t_map *map)
{
	return (0);
}

int	check_rectangle(t_map *map)
{
	int	i;

	i = 0;
	while (map->map[i])
		if (ft_strlen(map->map[i++]) != map->col_count)
			return (1);
	return (0);
}

int	is_legal_char(char ch)
{
	if (ch == '1' || ch == '0' || ch == 'P' || ch == 'E' || ch == 'C')
		return (0);
	return (1);
}

int	check_illegal_char(t_map *map)
{
	int	i;
	int	j;
	int	flag[2];

	ft_memset(flag, 0, (sizeof(int) * 2));
	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == 'P')
				flag[0]++;
			if (map->map[i][j] == 'E')
				flag[1]++;
			if (is_legal_char(map->map[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	if (flag[0] != 1 || flag[1] != 1)
		return (1);
	return (0);
}

int	check_borders(t_map *map)
{
	int	i;

	i = 0;
	map->col_count = ft_strlen(map->map[0]);
	while (i < map->col_count)
		if (map->map[0][i++] != '1')
			return (1);
	i = 0;
	while (i < map->row_count)
		if (map->map[i++][0] != '1')
			return (1);
	i = 0;
	while (i < map->row_count)
		if (map->map[i++][map->col_count - 1] != '1')
			return (1);
	i = 0;
	while (i < map->col_count)
		if (map->map[map->row_count - 1][i++] != '1')
			return (1);
	return (0);
}

int	validate_map(t_map *map)
{
	if (check_borders(map) || check_illegal_char(map)
		|| check_rectangle(map) || check_escape(map))
		return (1);
	return (0);
}

int	destructor(t_map *map)
{
	int	i;

	i = 0;
	while (map->map[i])
		free(map->map[i++]);
	free(map->map);
}

int	main(int argc, char *argv[])
{
	t_map	map;

	if (argc != 2)
		return (ft_printf("Invalid number of arguments\n"), 1);
	if (check_extension(argv[1]))
		return (ft_printf("Invalid file extension\n"), 1);
	if (read_map(argv[1], &map))
		return (ft_printf("Failed to read the file or empty file\n", 1));
	if (validate_map(&map))
		return (destructor(&map), ft_printf("Invalid map\n"), 1);
	print_map(&map);
	destructor(&map);
	return (0);
}
