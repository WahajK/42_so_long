/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:52:20 by muhakhan          #+#    #+#             */
/*   Updated: 2025/05/24 15:06:38 by muhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	ft_check_extension(char *fname)
{
	if (ft_strncmp(&fname[ft_strlen(fname) - 4], ".ber", 4) != 0)
		return (1);
	return (0);
}

int	ft_get_row_count(char *fname)
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

char	*ft_trim(char *arr)
{
	if (arr[ft_strlen(arr) - 1] == '\n')
		arr[ft_strlen(arr) - 1] = 0;
	return (arr);
}

int	ft_read_map(char *fname, t_map *map)
{
	int		fd;
	int		i;
	char	*temp;

	fd = open(fname, O_RDONLY);
	if (fd < 0)
		return (1);
	map->row_count = ft_get_row_count(fname);
	map->map = malloc((map->row_count + 1) * sizeof(char *));
	temp = get_next_line(fd);
	i = 0;
	while (temp)
	{
		map->map[i++] = ft_trim(temp);
		temp = get_next_line(fd);
	}
	map->map[i] = NULL;
	close(fd);
	return (0);
}

int	main(int argc, char *argv[])
{
	t_map	map;

	if (argc != 2)
		return (ft_printf("Invalid number of arguments\n"), 1);
	if (ft_check_extension(argv[1]))
		return (ft_printf("Invalid file extension\n"), 1);
	if (ft_read_map(argv[1], &map))
		return (ft_printf("Failed to open the file\n", 1));
	int i = 0;
	while (map.map[i])
	{
		ft_printf("%s\n", map.map[i++]);
	}
	return (0);
}
