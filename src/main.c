/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:52:20 by muhakhan          #+#    #+#             */
/*   Updated: 2025/06/02 00:17:14 by muhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

void	destructor_map(char **map);

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

int	illegal_char(int row, char *str, t_map *map)
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
				map->player_pos[0] = row;
				map->player_pos[1] = i;
			}
		}
		else
			return (1);
		i++;
	}
	return (0);
}

int	set_counts(t_map *map, char *fname)
{
	int		fd;
	char	*str;
	int		flag[2];

	ft_bzero(flag, sizeof(int) * 2);
	fd = open(fname, O_RDONLY);
	if (fd < 0)
		return (1);
	str = trim(get_next_line(fd));
	map->x_count = ft_strlen(str);
	while (str && ++flag[0])
	{
		if ((int) ft_strlen(str) != map->x_count
			|| illegal_char(flag[0] - 1, str, map))
			flag[1] = 1;
		map->c_count += char_count(str, 'C');
		map->p_count += char_count(str, 'P');
		map->e_count += char_count(str, 'E');
		map->x_count += char_count(str, 'X');
		free(str);
		str = trim(get_next_line(fd));
	}
	if (!map->c_count || map->p_count != 1 || map->e_count != 1 || flag[1])
		return (close (fd), 1);
	return (map->y_count = flag[0], close (fd), 0);
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
	map->map = malloc((map->y_count + 1) * sizeof(char *));
	if (!map->map)
		return (close(fd), 1);
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

int	check_escape(t_map *map)
{
	char	**map_copy;
	int		flags[2];

	ft_bzero(flags, sizeof(int) * 2);
	map_copy = dup_map(map->y_count, map->map);
	solve_maze(map_copy, flags, map->player_pos[0], map->player_pos[1]);
	if (!flags[0] || !flags[1])
		return (destructor_map(map_copy), 1);
	return (destructor_map(map_copy), 0);
}

int	check_borders(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->x_count)
		if (map->map[0][i++] != '1')
			return (1);
	i = 0;
	while (i < map->y_count)
		if (map->map[i++][0] != '1')
			return (1);
	i = 0;
	while (i < map->y_count)
		if (map->map[i++][map->x_count - 1] != '1')
			return (1);
	i = 0;
	while (i < map->x_count)
		if (map->map[map->y_count - 1][i++] != '1')
			return (1);
	return (0);
}

int	validate_map(t_map *map)
{
	if (check_borders(map) || check_escape(map))
		return (1);
	return (0);
}

void	destructor_map(char **map)
{
	int	i;

	i = 0;
	while (map[i])
		free(map[i++]);
	free(map);
}

void	destructor(t_map *map)
{
	destructor_map(map->map);
	exit(1);
}

void	start_game_window(t_map *map)
{
	int	size_x;
	int	size_y;
	map->mlx = mlx_init();
	if (!map->mlx)
		destructor(map);
	mlx_get_screen_size(map->mlx, &size_x, &size_y);
	if (map->x_count * TILE_SIZE > size_x || map->y_count * TILE_SIZE > size_y)
		return (ft_printf("Screen too big\n"), destructor(map));
	map->window = mlx_new_window(map->mlx, map->x_count * TILE_SIZE \
		, map->y_count * TILE_SIZE, "Meow");
	if (!map->window)
		destructor(map);
}

void	set_tiles(t_map *map)
{
	int	tile_size;

	tile_size = TILE_SIZE;
	map->player = mlx_xpm_file_to_image(map->mlx, "character_.xpm",
				&tile_size, &tile_size);
	map->temp = mlx_xpm_file_to_image(map->mlx, "character_.xpm",
				&tile_size, &tile_size);
}

void	draw_image(t_map *map, void *img, int x, int y)
{
	mlx_put_image_to_window(map->mlx, map->window, img, TILE_SIZE * x, TILE_SIZE * y);
}

void	render_map(t_map *map)
{
	int	i;
	int	j;

	set_tiles(map);
	i = 0;
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
			draw_image(map, map->player, j++, i);
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_map	map;

	ft_bzero(&map, sizeof(t_map));
	if (argc != 2)
		return (ft_printf("Invalid number of arguments\n"), 1);
	if (check_extension(argv[1]) || read_map(argv[1], &map))
		return (ft_printf("Invalid map or file\n"), 1);
	if (validate_map(&map))
		return (destructor(&map), ft_printf("Invalid map\n"), 1);
	start_game_window(&map);
	render_map(&map);
	mlx_loop(map.mlx);
	return (destructor(&map), 0);
}
