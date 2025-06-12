/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:52:20 by muhakhan          #+#    #+#             */
/*   Updated: 2025/06/12 15:40:57 by muhakhan         ###   ########.fr       */
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
	if ((map->x_count + 2) * TILE_SIZE > size_x
		|| (map->y_count + 2) * TILE_SIZE > size_y)
		return (ft_printf("Screen too big\n"), destructor(map));
	map->window = mlx_new_window(map->mlx, (map->x_count + 2) * TILE_SIZE \
		, (map->y_count + 2) * TILE_SIZE, "Meow");
	if (!map->window)
		destructor(map);
}

void	set_tiles(t_map *map)
{
	int		tile_size;
	void	*(*f)(void *, char *, int *, int *);

	tile_size = TILE_SIZE;
	f = mlx_xpm_file_to_image;
	map->obstacle = f(map->mlx, OBSTACLE, &tile_size, &tile_size);
	map->background = f(map->mlx, BACKGROUND, &tile_size, &tile_size);
	map->player_down = f(map->mlx, PLAYER_DOWN, &tile_size, &tile_size);
	map->player_up = f(map->mlx, PLAYER_UP, &tile_size, &tile_size);
	map->player_left = f(map->mlx, PLAYER_LEFT, &tile_size, &tile_size);
	map->player_right = f(map->mlx, PLAYER_RIGHT, &tile_size, &tile_size);
	map->water = f(map->mlx, WATER, &tile_size, &tile_size);
	map->exit_active = f(map->mlx, EXIT_ACTIVE, &tile_size, &tile_size);
	map->exit_inactive = f(map->mlx, EXIT_INACTIVE, &tile_size, &tile_size);
	map->bot_left_tile = f(map->mlx, BOT_LEFT_TILE, &tile_size, &tile_size);
	map->bot_right_tile = f(map->mlx, BOT_RIGHT_TILE, &tile_size, &tile_size);
	map->bot_tile = f(map->mlx, BOT_TILE, &tile_size, &tile_size);
	map->top_left_tile = f(map->mlx, TOP_LEFT_TILE, &tile_size, &tile_size);
	map->top_right_tile = f(map->mlx, TOP_RIGHT_TILE, &tile_size, &tile_size);
	map->top_tile = f(map->mlx, TOP_TILE, &tile_size, &tile_size);
	map->left_tile = f(map->mlx, LEFT_TILE, &tile_size, &tile_size);
	map->right_tile = f(map->mlx, RIGHT_TILE, &tile_size, &tile_size);
	map->collectible = f(map->mlx, COLLECTIBLE, &tile_size, &tile_size);
}

void	draw_image(t_map *map, void *img, int x, int y)
{
	mlx_put_image_to_window(map->mlx, map->window, \
		img, TILE_SIZE * x, TILE_SIZE * y);
}

void	draw_water(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->x_count + 2)
		draw_image(map, map->water, i++, 0);
	i = 0;
	while (i < map->y_count + 2)
		draw_image(map, map->water, 0, i++);
	i = 0;
	while (i < map->x_count + 2)
		draw_image(map, map->water, i++, map->y_count + 1);
	i = 0;
	while (i < map->x_count + 2)
		draw_image(map, map->water, map->x_count + 1, i++);
}

void	draw_border(t_map *map)
{
	int	i;

	i = 1;
	while (i < map->x_count + 1)
	{
		if (i == 1)
			draw_image(map, map->top_left_tile, i++, 1);
		else if (i == map->x_count)
			draw_image(map, map->top_right_tile, i++, 1);
		else
			draw_image(map, map->top_tile, i++, 1);
	}
	i = 1;
	while (i < map->x_count + 1)
	{
		if (i == 1)
			draw_image(map, map->bot_left_tile, i++, map->y_count);
		else if (i == map->x_count)
			draw_image(map, map->bot_right_tile, i++, map->y_count);
		else
			draw_image(map, map->bot_tile, i++, map->y_count);
	}
	continue_border(map);
}

void	continue_border(t_map *map)
{
	int	i;

	i = 2;
	while (i < map->y_count)
		draw_image(map, map->left_tile, 1, i++);
	i = 2;
	while (i < map->y_count)
		draw_image(map, map->right_tile, map->x_count, i++);
}

void	render_map(t_map *map)
{
	int	i;
	int	j;

	set_tiles(map);
	draw_water(map);
	draw_border(map);
	i = 1;
	while (map->map[i + 1])
	{
		j = 1;
		while (map->map[i][j + 1])
		{
			if (map->map[i][j] == '1')
				draw_image(map, map->obstacle, j + 1, i + 1);
			else if (map->map[i][j] == 'P')
				draw_image(map, map->player_right, j + 1, i + 1);
			else if (map->map[i][j] == 'E')
				draw_image(map, map->exit_inactive, j + 1, i + 1);
			else if (map->map[i][j] == 'C')
				draw_image(map, map->collectible, j + 1, i + 1);
			else
				draw_image(map, map->background, j + 1, i + 1);
			j++;
		}
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
