/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 14:24:29 by avillar           #+#    #+#             */
/*   Updated: 2022/08/30 11:34:32 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

int	check_if_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	parsing_check_int(char **arg)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (check_if_digit(arg[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

int	parsing_glo(int argc, char **argv)
{
	if (argc == 1)
	{
		write (2, "1 = num of philo, 2 = time to die, 3 = time to eat\n", 51);
		write (2, "4 = time to sleep and 5 = num of time to eat ", 45);
		write (2, "can be not set\n", 15);
		return (1);
	}
	if (argc < 5 || argc > 6)
	{
		write (2, "Wrong number of arguments.\n", 27);
		return (1);
	}
	if (parsing_check_int(argv) == 1)
	{
		write (2, "wrong syntaxe try numbers\n", 26);
		return (1);
	}
	if (ft_atoi(argv[1]) < 1)
	{
		write (2, "try a number of philo > 0\n", 26);
		return (1);
	}
	return (0);
}