/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 14:13:08 by hkonstan          #+#    #+#             */
/*   Updated: 2026/02/27 10:33:07 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	destroy_forks_mutex(t_total *total)
{
	int	i;

	i = 0;
	while (i < total->num_philosophers)
	{
		pthread_mutex_destroy(&total->forks[i]);
		i++;
	}
	free(total->forks);
}

void	destroy_philo_mutex(t_total *total)
{
	int	i;

	i = 0;
	while (i < total->num_philosophers)
	{
		pthread_mutex_destroy(&total->philosophers[i].eat_mutex);
		i++;
	}
	free(total->philosophers);
}

void	destroy_state_print_mutex(t_total *total)
{
	pthread_mutex_destroy(&total->print_mutex);
	pthread_mutex_destroy(&total->state_mutex);
}

void	free_all(t_total *total)
{
	destroy_philo_mutex(total);
	destroy_forks_mutex(total);
	destroy_state_print_mutex(total);
}
