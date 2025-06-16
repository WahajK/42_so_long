/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:52:20 by muhakhan          #+#    #+#             */
/*   Updated: 2025/06/16 19:10:53 by muhakhan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/so_long.h"

int	main(int argc, char *argv[])
{
	t_vars	vars;

	vars.steps = 0;
	ft_bzero(&vars, sizeof(t_vars));
	if (argc != 2)
		return (ft_printf("Invalid number of arguments\n"), 1);
	if (check_extension(argv[1]) || read_map(argv[1], &vars))
		return (destructor_map(vars.map), \
		ft_printf("Invalid map or file\n"), 1);
	if (validate_map(&vars))
		destructor(&vars, "Invalid Map");
	start_game_window(&vars);
	set_tiles(&vars);
	init_enemies(&vars);
	mlx_hook(vars.window, 2, 1L << 0, &handle_key, &vars);
	mlx_hook(vars.window, 17, 0, &handle_exit, &vars);
	mlx_loop_hook(vars.mlx, &update_game, &vars);
	mlx_loop(vars.mlx);
	return (0);
}
