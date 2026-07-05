/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 20:47:55 by hkonstan          #+#    #+#             */
/*   Updated: 2026/02/19 20:48:06 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	check_number(char *str)
{
	int			i;
	long long	num;

	i = 0;
	num = 0;
	while (str[i])
		num = num * 10 + (str[i++] - '0');
	if (num > 2147483647 || num == 0)
		return (0);
	return (num);
}

int	check_input(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 5 || argc > 6)
	{
		printf("Wrong amount of arguments!\n");
		return (0);
	}
	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (printf("Wrong argument: %s\n", argv[i]), 0);
			j++;
		}
		if (!check_number(argv[i]))
			return (printf("Argument out of range: %s\n", argv[i]), 0);
		i++;
	}
	return (1);
}
