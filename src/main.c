/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:52:20 by muhakhan          #+#    #+#             */
/*   Updated: 2025/05/29 20:55:02 by muhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	check_extension(char *fname)
{
	if (ft_strncmp(&fname[ft_strlen(fname) - 4], ".ber", 4) != 0)
		return (1);
	return (0);
}

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

int	illegal_char(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '0' || str[i] == '1' || str[i] == 'P'
			|| str[i] == 'E' || str[i] == 'C' || str[i] == 'X')
			i++;
		else
			return (1);
	}
	return (0);
}

int	set_counts(t_map *map, char *fname)
{
	int		fd;
	int		i;
	char	*str;

	i = 0;
	fd = open(fname, O_RDONLY);
	if (fd < 0)
		return (1);
	str = trim(get_next_line(fd));
	map->col_count = ft_strlen(str);
	while (str && ++i)
	{
		if (ft_strlen(str) != map->col_count || illegal_char(str))
			return (1);
		map->c_count += char_count(str, 'C');
		map->p_count += char_count(str, 'P');
		map->e_count += char_count(str, 'E');
		map->x_count += char_count(str, 'X');
		free(str);
		str = trim(get_next_line(fd));
	}
	if (!map->c_count || map->p_count != 1 || map->e_count != 1)
		return (close (fd), 1);
	return (map->row_count = i, close (fd), 0);
}

int	read_map(char *fname, t_map *map)
{
	int		fd;
	int		i;
	char	*temp;

	if (set_counts(map, fname))
		return (1);
	fd = open(fname, O_RDONLY);
	if (fd < 0)
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

int	check_escape(t_map *map)
{
	// char	**map_copy;

	// map_copy = dup_map(map->row_count, map->map);
	return (0);
}

int	check_borders(t_map *map)
{
	int	i;

	i = 0;
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
	int	flag;

	if (check_borders(map) || check_escape(map))
		return (1);
	return (0);
}

int	destructor(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

int	main(int argc, char *argv[])
{
	t_map	map;

	ft_bzero(&map, sizeof(t_map));
	if (argc != 2)
		return (ft_printf("Invalid number of arguments\n"), 1);
	if (check_extension(argv[1]) || read_map(argv[1], &map))
		return (ft_printf("Invalid map or file\n", 1));
	if (validate_map(&map))
		return (destructor(&map), ft_printf("Invalid map\n"), 1);
	print_map(&map);
	destructor(&map);
	return (0);
}
