/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:52:20 by muhakhan          #+#    #+#             */
/*   Updated: 2025/06/15 18:43:35 by muhakhan         ###   ########.fr       */
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

int	illegal_char(int row, char *str, t_vars *map)
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
				map->player.x = row;
				map->player.y = i;
			}
		}
		else
			return (1);
		i++;
	}
	return (0);
}

int	set_counts(t_vars *map, char *fname)
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
		map->ex_count += char_count(str, 'X');
		free(str);
		str = trim(get_next_line(fd));
	}
	if (!map->c_count || map->p_count != 1 || map->e_count != 1 || flag[1])
		return (close (fd), 1);
	return (map->y_count = flag[0], close (fd), 0);
}

int	read_map(char *fname, t_vars *map)
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
		map->map[i] = trim(temp);
		temp = get_next_line(fd);
		i++;
	}
	map->map[i] = NULL;
	close(fd);
	return (0);
}

void	print_map(t_vars *map)
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

int	check_escape(t_vars *map)
{
	char	**map_copy;
	int		flags[2];

	ft_bzero(flags, sizeof(int) * 2);
	map_copy = dup_map(map->y_count, map->map);
	solve_maze(map_copy, flags, map->player.x, map->player.y);
	if (!flags[0] || !flags[1])
		return (destructor_map(map_copy), 1);
	return (destructor_map(map_copy), 0);
}

int	check_borders(t_vars *map)
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

int	validate_map(t_vars *map)
{
	if (check_borders(map) || check_escape(map))
		return (1);
	return (0);
}

void	destructor_map(char **map)
{
	int	i;

	i = 0;
	if (!map)
		return ;
	while (map[i])
		free(map[i++]);
	free(map);
}

void	destroy_enemy_images(t_vars *var)
{
	int	i;
	int	j;

	i = 0;
	while (i < 1)
	{
		j = 0;
		while (j < 7)
			mlx_destroy_image(var->mlx, var->enemies->frames[i][j++]);
		i++;
	}
}

void	destroy_collectible_images(t_vars *var)
{
	int	i;

	i = 0;
	while (i < 7)
		mlx_destroy_image(var->mlx, var->collectibles.frames[i++]);
}

void	free_player_images(t_vars *vars)
{
	int	i;
	int	j;

	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < 6)
			mlx_destroy_image(vars->mlx, vars->player.frames[i][j++]);
		i++;
	}
}

void	destroy_obstacle_images(t_vars *vars)
{
	int	i;

	i = 0;
	while (i < 8)
		if (vars->obstacle.frames[i])
			mlx_destroy_image(vars->mlx, vars->obstacle.frames[i++]);
}

void	destroy_images(t_vars *map)
{
	destroy_obstacle_images(map);
	if (map->background)
		mlx_destroy_image(map->mlx, map->background);
	free_player_images(map);
	if (map->ex_count != 0)
		destroy_enemy_images(map);
	if (map->water)
		mlx_destroy_image(map->mlx, map->water);
	if (map->exit.img)
	{
		mlx_destroy_image(map->mlx, map->exit.img[0]);
		mlx_destroy_image(map->mlx, map->exit.img[1]);
	}
	if (map->collectibles.frames[0])
		destroy_collectible_images(map);
}

void	destructor(t_vars *map)
{
	destructor_map(map->map);
	destroy_images(map);
	if (map->window)
		mlx_destroy_window(map->mlx, map->window);
	if (map->mlx)
	{
		mlx_destroy_display(map->mlx);
		free(map->mlx);
	}
	free(map->enemies);
	exit(0);
}

void	start_game_window(t_vars *map)
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

void	set_obstacles(t_vars *vars, int tile_size)
{
	void	*(*f)(void *, char *, int *, int *);

	f = mlx_xpm_file_to_image;
	vars->obstacle.frames[0] = f(vars->mlx, OBSTACLE1, &tile_size, &tile_size);
	vars->obstacle.frames[1] = f(vars->mlx, OBSTACLE2, &tile_size, &tile_size);
	vars->obstacle.frames[2] = f(vars->mlx, OBSTACLE3, &tile_size, &tile_size);
	vars->obstacle.frames[3] = f(vars->mlx, OBSTACLE4, &tile_size, &tile_size);
	vars->obstacle.frames[4] = f(vars->mlx, OBSTACLE5, &tile_size, &tile_size);
	vars->obstacle.frames[5] = f(vars->mlx, OBSTACLE6, &tile_size, &tile_size);
	vars->obstacle.frames[6] = f(vars->mlx, OBSTACLE7, &tile_size, &tile_size);
	vars->obstacle.frames[7] = f(vars->mlx, OBSTACLE8, &tile_size, &tile_size);
}

void	set_player(t_vars *vars, int tile_size)
{
	void	*(*f)(void *, char *, int *, int *);

	f = mlx_xpm_file_to_image;
	vars->player.frames[0][0] = f(vars->mlx, PLAYER_RIGHT1, &tile_size, &tile_size);
	vars->player.frames[0][1] = f(vars->mlx, PLAYER_RIGHT2, &tile_size, &tile_size);
	vars->player.frames[0][2] = f(vars->mlx, PLAYER_RIGHT3, &tile_size, &tile_size);
	vars->player.frames[0][3] = f(vars->mlx, PLAYER_RIGHT4, &tile_size, &tile_size);
	vars->player.frames[0][4] = f(vars->mlx, PLAYER_RIGHT5, &tile_size, &tile_size);
	vars->player.frames[0][5] = f(vars->mlx, PLAYER_RIGHT6, &tile_size, &tile_size);
	vars->player.frames[1][0] = f(vars->mlx, PLAYER_LEFT1, &tile_size, &tile_size);
	vars->player.frames[1][1] = f(vars->mlx, PLAYER_LEFT2, &tile_size, &tile_size);
	vars->player.frames[1][2] = f(vars->mlx, PLAYER_LEFT3, &tile_size, &tile_size);
	vars->player.frames[1][3] = f(vars->mlx, PLAYER_LEFT4, &tile_size, &tile_size);
	vars->player.frames[1][4] = f(vars->mlx, PLAYER_LEFT5, &tile_size, &tile_size);
	vars->player.frames[1][5] = f(vars->mlx, PLAYER_LEFT6, &tile_size, &tile_size);
}

void	set_enemies(t_vars *vars, int tile_size)
{
	void	*(*f)(void *, char *, int *, int *);
	int		i;

	f = mlx_xpm_file_to_image;
	i = 0;
	vars->en_frames[0][0] = f(vars->mlx, ENEMY_RIGHT1, &tile_size, &tile_size);
	vars->en_frames[0][1] = f(vars->mlx, ENEMY_RIGHT2, &tile_size, &tile_size);
	vars->en_frames[0][2] = f(vars->mlx, ENEMY_RIGHT3, &tile_size, &tile_size);
	vars->en_frames[0][3] = f(vars->mlx, ENEMY_RIGHT4, &tile_size, &tile_size);
	vars->en_frames[0][4] = f(vars->mlx, ENEMY_RIGHT5, &tile_size, &tile_size);
	vars->en_frames[0][5] = f(vars->mlx, ENEMY_RIGHT6, &tile_size, &tile_size);
	vars->en_frames[0][6] = f(vars->mlx, ENEMY_RIGHT7, &tile_size, &tile_size);
	vars->en_frames[1][0] = f(vars->mlx, ENEMY_LEFT1, &tile_size, &tile_size);
	vars->en_frames[1][1] = f(vars->mlx, ENEMY_LEFT2, &tile_size, &tile_size);
	vars->en_frames[1][2] = f(vars->mlx, ENEMY_LEFT3, &tile_size, &tile_size);
	vars->en_frames[1][3] = f(vars->mlx, ENEMY_LEFT4, &tile_size, &tile_size);
	vars->en_frames[1][4] = f(vars->mlx, ENEMY_LEFT5, &tile_size, &tile_size);
	vars->en_frames[1][5] = f(vars->mlx, ENEMY_LEFT6, &tile_size, &tile_size);
	vars->en_frames[1][6] = f(vars->mlx, ENEMY_LEFT7, &tile_size, &tile_size);
}

void	set_collectibles(t_vars *vars, int tile_size)
{
	void	*(*f)(void *, char *, int *, int *);

	f = mlx_xpm_file_to_image;
	vars->collectibles.frames[0] = f(vars->mlx, COLLECTIBLE1, &tile_size, &tile_size);
	vars->collectibles.frames[1] = f(vars->mlx, COLLECTIBLE2, &tile_size, &tile_size);
	vars->collectibles.frames[2] = f(vars->mlx, COLLECTIBLE3, &tile_size, &tile_size);
	vars->collectibles.frames[3] = f(vars->mlx, COLLECTIBLE4, &tile_size, &tile_size);
	vars->collectibles.frames[4] = f(vars->mlx, COLLECTIBLE5, &tile_size, &tile_size);
	vars->collectibles.frames[5] = f(vars->mlx, COLLECTIBLE6, &tile_size, &tile_size);
	vars->collectibles.frames[6] = f(vars->mlx, COLLECTIBLE7, &tile_size, &tile_size);
}

void	set_tiles(t_vars *vars)
{
	int		tile_size;
	void	*(*f)(void *, char *, int *, int *);

	tile_size = TILE_SIZE;
	f = mlx_xpm_file_to_image;
	set_obstacles(vars, tile_size);
	set_player(vars, tile_size);
	vars->background = f(vars->mlx, BACKGROUND, &tile_size, &tile_size);
	if (vars->ex_count != 0)
		set_enemies(vars, tile_size);
	vars->water = f(vars->mlx, WATER, &tile_size, &tile_size);
	vars->exit.img[0] = f(vars->mlx, EXIT_INACTIVE, &tile_size, &tile_size);
	vars->exit.img[1] = f(vars->mlx, EXIT_ACTIVE, &tile_size, &tile_size);
	vars->borders.frames[0][0] = f(vars->mlx, TOP_LEFT1, &tile_size, &tile_size);
	vars->borders.frames[0][1] = f(vars->mlx, TOP_LEFT2, &tile_size, &tile_size);
	vars->borders.frames[0][2] = f(vars->mlx, TOP_LEFT3, &tile_size, &tile_size);
	vars->borders.frames[0][3] = f(vars->mlx, TOP_LEFT4, &tile_size, &tile_size);
	vars->borders.frames[0][4] = f(vars->mlx, TOP_LEFT5, &tile_size, &tile_size);
	vars->borders.frames[0][5] = f(vars->mlx, TOP_LEFT6, &tile_size, &tile_size);
	vars->borders.frames[0][6] = f(vars->mlx, TOP_LEFT7, &tile_size, &tile_size);
	vars->borders.frames[0][7] = f(vars->mlx, TOP_LEFT8, &tile_size, &tile_size);
	vars->borders.frames[1][0] = f(vars->mlx, TOP_1, &tile_size, &tile_size);
	vars->borders.frames[1][1] = f(vars->mlx, TOP_2, &tile_size, &tile_size);
	vars->borders.frames[1][2] = f(vars->mlx, TOP_3, &tile_size, &tile_size);
	vars->borders.frames[1][3] = f(vars->mlx, TOP_4, &tile_size, &tile_size);
	vars->borders.frames[1][4] = f(vars->mlx, TOP_5, &tile_size, &tile_size);
	vars->borders.frames[1][5] = f(vars->mlx, TOP_6, &tile_size, &tile_size);
	vars->borders.frames[1][6] = f(vars->mlx, TOP_7, &tile_size, &tile_size);
	vars->borders.frames[1][7] = f(vars->mlx, TOP_8, &tile_size, &tile_size);
	vars->borders.frames[2][0] = f(vars->mlx, TOP_RIGHT1, &tile_size, &tile_size);
	vars->borders.frames[2][1] = f(vars->mlx, TOP_RIGHT2, &tile_size, &tile_size);
	vars->borders.frames[2][2] = f(vars->mlx, TOP_RIGHT3, &tile_size, &tile_size);
	vars->borders.frames[2][3] = f(vars->mlx, TOP_RIGHT4, &tile_size, &tile_size);
	vars->borders.frames[2][4] = f(vars->mlx, TOP_RIGHT5, &tile_size, &tile_size);
	vars->borders.frames[2][5] = f(vars->mlx, TOP_RIGHT6, &tile_size, &tile_size);
	vars->borders.frames[2][6] = f(vars->mlx, TOP_RIGHT7, &tile_size, &tile_size);
	vars->borders.frames[2][7] = f(vars->mlx, TOP_RIGHT8, &tile_size, &tile_size);
	vars->borders.frames[3][0] = f(vars->mlx, LEFT1, &tile_size, &tile_size);
	vars->borders.frames[3][1] = f(vars->mlx, LEFT2, &tile_size, &tile_size);
	vars->borders.frames[3][2] = f(vars->mlx, LEFT3, &tile_size, &tile_size);
	vars->borders.frames[3][3] = f(vars->mlx, LEFT4, &tile_size, &tile_size);
	vars->borders.frames[3][4] = f(vars->mlx, LEFT5, &tile_size, &tile_size);
	vars->borders.frames[3][5] = f(vars->mlx, LEFT6, &tile_size, &tile_size);
	vars->borders.frames[3][6] = f(vars->mlx, LEFT7, &tile_size, &tile_size);
	vars->borders.frames[3][7] = f(vars->mlx, LEFT8, &tile_size, &tile_size);
	vars->borders.frames[4][0] = f(vars->mlx, RIGHT1, &tile_size, &tile_size);
	vars->borders.frames[4][1] = f(vars->mlx, RIGHT2, &tile_size, &tile_size);
	vars->borders.frames[4][2] = f(vars->mlx, RIGHT3, &tile_size, &tile_size);
	vars->borders.frames[4][3] = f(vars->mlx, RIGHT4, &tile_size, &tile_size);
	vars->borders.frames[4][4] = f(vars->mlx, RIGHT5, &tile_size, &tile_size);
	vars->borders.frames[4][5] = f(vars->mlx, RIGHT6, &tile_size, &tile_size);
	vars->borders.frames[4][6] = f(vars->mlx, RIGHT7, &tile_size, &tile_size);
	vars->borders.frames[4][7] = f(vars->mlx, RIGHT8, &tile_size, &tile_size);
	vars->borders.frames[5][0] = f(vars->mlx, BOT_LEFT1, &tile_size, &tile_size);
	vars->borders.frames[5][1] = f(vars->mlx, BOT_LEFT2, &tile_size, &tile_size);
	vars->borders.frames[5][2] = f(vars->mlx, BOT_LEFT3, &tile_size, &tile_size);
	vars->borders.frames[5][3] = f(vars->mlx, BOT_LEFT4, &tile_size, &tile_size);
	vars->borders.frames[5][4] = f(vars->mlx, BOT_LEFT5, &tile_size, &tile_size);
	vars->borders.frames[5][5] = f(vars->mlx, BOT_LEFT6, &tile_size, &tile_size);
	vars->borders.frames[5][6] = f(vars->mlx, BOT_LEFT7, &tile_size, &tile_size);
	vars->borders.frames[5][7] = f(vars->mlx, BOT_LEFT8, &tile_size, &tile_size);
	vars->borders.frames[6][0] = f(vars->mlx, BOT_1, &tile_size, &tile_size);
	vars->borders.frames[6][1] = f(vars->mlx, BOT_2, &tile_size, &tile_size);
	vars->borders.frames[6][2] = f(vars->mlx, BOT_3, &tile_size, &tile_size);
	vars->borders.frames[6][3] = f(vars->mlx, BOT_4, &tile_size, &tile_size);
	vars->borders.frames[6][4] = f(vars->mlx, BOT_5, &tile_size, &tile_size);
	vars->borders.frames[6][5] = f(vars->mlx, BOT_6, &tile_size, &tile_size);
	vars->borders.frames[6][6] = f(vars->mlx, BOT_7, &tile_size, &tile_size);
	vars->borders.frames[6][7] = f(vars->mlx, BOT_8, &tile_size, &tile_size);
	vars->borders.frames[7][0] = f(vars->mlx, BOT_RIGHT1, &tile_size, &tile_size);
	vars->borders.frames[7][1] = f(vars->mlx, BOT_RIGHT2, &tile_size, &tile_size);
	vars->borders.frames[7][2] = f(vars->mlx, BOT_RIGHT3, &tile_size, &tile_size);
	vars->borders.frames[7][3] = f(vars->mlx, BOT_RIGHT4, &tile_size, &tile_size);
	vars->borders.frames[7][4] = f(vars->mlx, BOT_RIGHT5, &tile_size, &tile_size);
	vars->borders.frames[7][5] = f(vars->mlx, BOT_RIGHT6, &tile_size, &tile_size);
	vars->borders.frames[7][6] = f(vars->mlx, BOT_RIGHT7, &tile_size, &tile_size);
	vars->borders.frames[7][7] = f(vars->mlx, BOT_RIGHT8, &tile_size, &tile_size);
	set_collectibles(vars, tile_size);
}

void	draw_image(t_vars *map, void *img, int x, int y)
{
	mlx_put_image_to_window(map->mlx, map->window, \
		img, TILE_SIZE * x, TILE_SIZE * y);
}

void	draw_water(t_vars *map)
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

void	draw_border(t_vars *map)
{
	int	i;

	i = 1;
	while (i < map->x_count + 1)
	{
		if (i == 1)
			draw_image(map, map->borders.frames[0][map->borders.frame_index], i++, 1);
		else if (i == map->x_count)
			draw_image(map, map->borders.frames[2][map->borders.frame_index], i++, 1);
		else
			draw_image(map, map->borders.frames[1][map->borders.frame_index], i++, 1);
	}
	i = 1;
	while (i < map->x_count + 1)
	{
		if (i == 1)
			draw_image(map, map->borders.frames[5][map->borders.frame_index], i++, map->y_count);
		else if (i == map->x_count)
			draw_image(map, map->borders.frames[7][map->borders.frame_index], i++, map->y_count);
		else
			draw_image(map, map->borders.frames[6][map->borders.frame_index], i++, map->y_count);
	}
	continue_border(map);
}

void	continue_border(t_vars *map)
{
	int	i;

	i = 2;
	while (i < map->y_count)
		draw_image(map, map->borders.frames[3][map->borders.frame_index], 1, i++);
	i = 2;
	while (i < map->y_count)
		draw_image(map, map->borders.frames[4][map->borders.frame_index], map->x_count, i++);
}

void	check_and_draw(t_vars *map, int i, int j)
{
	if (map->map[i][j] == '1')
		draw_image(map, map->obstacle.frames[map->obstacle.frame_index] \
			, j + 1, i + 1);
	else if (map->map[i][j] == 'P')
	{
		if (map->player.direction == 0)
			draw_image(map, map->player.frames[map->player.direction] \
				[map->player.frame_index], j + 1, i + 1);
		else if (map->player.direction == 1)
			draw_image(map, map->player.frames[map->player.direction] \
				[map->player.frame_index], j + 1, i + 1);
		else if (map->player.direction == 2)
			draw_image(map, map->player.frames[map->player.direction] \
				[map->player.frame_index], j + 1, i + 1);
		else if (map->player.direction == 3)
			draw_image(map, map->player.frames[map->player.direction] \
				[map->player.frame_index], j + 1, i + 1);
	}
	else if (map->map[i][j] == 'X')
	{
		int k = 0;
		while (k < map->ex_count)
		{
			if (map->enemies[k].x == j && map->enemies[k].y == i)
			{
				draw_image(map,
					map->enemies[k].frames[map->enemies[k].direction][map->enemies[k].frame_index],
					j + 1, i + 1);
				break;
			}
			k++;
		}
	}
	else if (map->map[i][j] == 'E')
		draw_image(map, map->exit.img[map->exit.flag], j + 1, i + 1);
	else if (map->map[i][j] == 'C')
		draw_image(map, map->collectibles.frames[map->collectibles. \
			frame_index], j + 1, i + 1);
	else
		draw_image(map, map->background, j + 1, i + 1);
}

void	render_map(t_vars *map)
{
	int	i;
	int	j;

	draw_water(map);
	draw_border(map);
	i = 1;
	while (map->map[i + 1])
	{
		j = 1;
		while (map->map[i][j + 1])
		{
			check_and_draw(map, i, j);
			j++;
		}
		i++;
	}
}

void	move_player(t_vars *map, int x, int y)
{
	if (map->map[map->player.x + x][map->player.y + y] == '1')
		return;
	if (map->map[map->player.x + x][map->player.y + y] == 'X')
	{
		destructor(map);
		return;
	}
	if (map->map[map->player.x + x][map->player.y + y] == 'E')
	{
		if (map->c_count == 0)
			destructor(map);
		return;
	}
	if (map->map[map->player.x + x][map->player.y + y] == 'C')
		map->c_count--;
	map->map[map->player.x][map->player.y] = '0';
	map->map[map->player.x + x][map->player.y + y] = 'P';                
	map->player.x = map->player.x + x;
	map->player.y = map->player.y + y;
	render_map(map);
}


int	handle_key(int keysym, t_vars *map)
{
	if (keysym == XK_w)
		move_player(map, -1, 0);
	if (keysym == XK_s)
		move_player(map, 1, 0);
	if (keysym == XK_a)
	{
		map->player.direction = 1;
		move_player(map, 0, -1);
	}
	if (keysym == XK_d)
	{
		map->player.direction = 0;
		move_player(map, 0, 1);
	}
	if (keysym == XK_Escape)
		destructor(map);
	return (0);
}

int	handle_exit(t_vars *map)
{
	destructor(map);
	return (0);
}

int	update_game(t_vars *vars)
{
	static int	frame = 0;

	frame++;
	if (frame % 300 == 0 && !vars->collectibles.flag)
	{
		vars->collectibles.frame_index++;
		if (vars->collectibles.frame_index >= 7)
		{
			vars->collectibles.frame_index = 6;
			vars->collectibles.flag = 1;
		}
	}
	if (frame % 300 == 0)
	{
		for (int i = 0; i < vars->ex_count; i++)
		{
			vars->enemies[i].frame_index++;
			if (vars->enemies[i].frame_index >= 7)
				vars->enemies[i].frame_index = 0;
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
	if (frame % 2000 == 0)
		move_enemies(vars);
	if (frame % 30 == 0)
	{
		if (vars->c_count == 0)
			vars->exit.flag = 1;
		render_map(vars);
	}
}

void	move_enemies(t_vars *vars)
{
	int	i;
	int next_x;
	char next_tile;
	t_enemy *e;

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
				destructor(vars); //lose
			vars->map[vars->enemies[i].y][vars->enemies[i].x] = '0';
			vars->enemies[i].x = next_x;
			vars->map[vars->enemies[i].y][vars->enemies[i].x] = 'X';
		}
		else
		{
			vars->enemies[i].direction = !vars->enemies[i].direction;
		}
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
				for (int d = 0; d < 2; d++)
					for (int f = 0; f < 7; f++)
						vars->enemies[count].frames[d][f] = vars->en_frames[d][f];
				count++;
			}
			j++;
		}
		i++;
	}
}

int	main(int argc, char *argv[])
{
	t_vars	vars;

	ft_bzero(&vars, sizeof(t_vars));
	if (argc != 2)
		return (ft_printf("Invalid number of arguments\n"), 1);
	if (check_extension(argv[1]) || read_map(argv[1], &vars))
		return (ft_printf("Invalid map or file\n"), 1);
	if (validate_map(&vars))
		return (destructor(&vars), ft_printf("Invalid map\n"), 1);
	start_game_window(&vars);
	set_tiles(&vars);
	init_enemies(&vars);
	mlx_hook(vars.window, 2, 1L << 0, &handle_key, &vars);
	mlx_hook(vars.window, 17, 0, &handle_exit, &vars);
	mlx_loop_hook(vars.mlx, &update_game, &vars);
	mlx_loop(vars.mlx);
	return (0);
}