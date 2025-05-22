/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muhakhan <muhakhan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/17 14:52:20 by muhakhan          #+#    #+#             */
/*   Updated: 2025/05/22 23:42:58 by muhakhan         ###   ########.fr       */
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
	int	fd;
	int	i;

	i = 0;
	fd = open(fname, O_RDONLY);
	if (fd < 0)
		return (1);
	while (get_next_line(fd))
		i++;
	close(fd);
	return (i);
}

int	read_map(char *fname)
{
	int	fd;

	fd = open(fname, O_RDONLY);
	if (fd < 0)
		return (1);
	close(fd);
	ft_printf("Row Count: %d\n", get_row_count(fname));
	return (0);
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
		return (ft_printf("Invalid number of arguments\n"), 1);
	if (check_extension(argv[1]))
		return (ft_printf("Invalid file extension\n"), 1);
	if (read_map(argv[1]))
		return (ft_printf("Failed to open the file\n", 1));
	return (0);
}
