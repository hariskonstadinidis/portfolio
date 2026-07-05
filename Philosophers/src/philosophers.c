/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hkonstan <hkonstan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/18 12:32:05 by hariskon          #+#    #+#             */
/*   Updated: 2026/02/27 11:04:56 by hkonstan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static int	get_one_fork(pthread_mutex_t *first_fork,
	pthread_mutex_t *second_fork, t_philo *philo)
{
	pthread_mutex_lock(first_fork);
	if (!print_message(philo, FORK))
		return (pthread_mutex_unlock(first_fork), 0);
	pthread_mutex_lock(second_fork);
	if (!print_message(philo, FORK))
		return (pthread_mutex_unlock(second_fork),
			pthread_mutex_unlock(first_fork), 0);
	if (!print_message(philo, EAT))
		return (pthread_mutex_unlock(second_fork),
			pthread_mutex_unlock(first_fork), 0);
	pthread_mutex_lock(&philo->eat_mutex);
	philo->last_eat_time = get_time(0);
	philo->times_eaten++;
	pthread_mutex_unlock(&philo->eat_mutex);
	ft_usleep(philo, philo->total->time_to_eat);
	pthread_mutex_unlock(first_fork);
	pthread_mutex_unlock(second_fork);
	return (1);
}

int	get_forks(t_philo *philo)
{
	int	id;

	id = philo->id;
	if (philo->total->num_philosophers == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		if (!print_message(philo, FORK))
			return (pthread_mutex_unlock(philo->left_fork), 0);
		pthread_mutex_unlock(philo->left_fork);
		ft_usleep(philo, philo->total->time_to_die + 1000);
	}
	if (id % 2 == 0)
	{
		if (!get_one_fork(philo->left_fork, philo->right_fork, philo))
			return (0);
	}
	else
	{
		if (!get_one_fork(philo->right_fork, philo->left_fork, philo))
			return (0);
	}
	return (1);
}

int	check_fed(t_total *total, int *fed_count, int i)
{
	if (total->num_meals == -1)
		return (1);
	if (total->philosophers[i].times_eaten >= total->num_meals)
		(*fed_count)++;
	if (*fed_count >= total->num_philosophers)
	{
		pthread_mutex_lock(&total->state_mutex);
		total->state = FED;
		pthread_mutex_unlock(&total->state_mutex);
		pthread_mutex_unlock(&total->philosophers[i].eat_mutex);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_total		total;

	if (!check_input(argc, argv))
		return (1);
	if (!initialize(&total, argv))
		return (1);
	if (!start_sim(&total))
		return (free_all(&total), 1);
	if (!end_sim(&total))
		return (free_all(&total), 1);
	free_all(&total);
	return (0);
}
