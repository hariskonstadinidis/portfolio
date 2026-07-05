/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simulation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariskon <hariskon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 19:10:28 by hariskon          #+#    #+#             */
/*   Updated: 2026/02/28 12:55:49 by hariskon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

static void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(&philo->total->print_mutex);
	pthread_mutex_unlock(&philo->total->print_mutex);
	if (philo->id % 2 != 0)
		ft_usleep(philo, philo->total->time_to_eat);
	while (1)
	{
		if (!get_forks(philo))
			return (NULL);
		if (!print_message (philo, SLEEP))
			return (NULL);
		ft_usleep(philo, philo->total->time_to_sleep);
		if (!print_message (philo, THINK))
			return (NULL);
		ft_usleep(philo, philo->total->time_to_think);
	}
	return (NULL);
}

static void	*fail_check(void *arg)
{
	t_total		*total;
	int			i;
	int			fed_count;

	total = (t_total *)arg;
	i = 0;
	while (1)
	{
		if (i == 0)
			fed_count = 0;
		pthread_mutex_lock(&total->philosophers[i].eat_mutex);
		if (get_time(total->philosophers[i].last_eat_time) > total->time_to_die)
			return (change_state(total, i), NULL);
		if (!check_fed(total, &fed_count, i))
			return (NULL);
		pthread_mutex_unlock(&total->philosophers[i++].eat_mutex);
		if (i == total->num_philosophers)
		{
			i = 0;
			usleep(500);
		}
	}
	return (NULL);
}

int	start_sim(t_total *total)
{
	int				i;

	total->time = get_time(0);
	i = 0;
	pthread_mutex_lock(&total->print_mutex);
	while (i < total->num_philosophers)
	{
		total->philosophers[i].last_eat_time = total->time;
		if (pthread_create(&total->philosophers[i].thread, NULL, routine,
				&total->philosophers[i]))
		{
			while (--i >= 0)
				if (pthread_join(total->philosophers[i].thread, NULL))
					return (write(2, "thread_join fail in start_sim\n", 30), 0);
			return (write(2, "pthread_init fail 1 in init_philos\n", 35), 0);
		}
		i++;
	}
	if (pthread_create(&total->monitor, NULL, fail_check, total))
		return (write(2, "pthread_init fail 2 in init_philos\n", 35), 0);
	pthread_mutex_unlock(&total->print_mutex);
	return (1);
}

int	end_sim(t_total *total)
{
	int	i;
	int	result;

	result = 1;
	i = 0;
	while (i < total->num_philosophers)
	{
		if (pthread_join(total->philosophers[i].thread, NULL))
		{
			write(2, "pthread_join fail 1 in end_sim\n", 31);
			result = 0;
		}
		i++;
	}
	if (pthread_join(total->monitor, NULL))
	{
		write(2, "pthread_join fail 1 in end_sim\n", 31);
		result = 0;
	}
	return (result);
}

int	print_message(t_philo *philo, t_state status)
{
	long long	time;

	time = get_time(philo->total->time);
	pthread_mutex_lock(&philo->total->print_mutex);
	pthread_mutex_lock(&philo->total->state_mutex);
	if (philo->total->state == DEAD || philo->total->state == FED)
	{
		pthread_mutex_unlock(&philo->total->state_mutex);
		pthread_mutex_unlock(&philo->total->print_mutex);
		return (0);
	}
	pthread_mutex_unlock(&philo->total->state_mutex);
	if (status == FORK)
		printf("%lli %i has taken a fork\n", time, philo->id + 1);
	else if (status == EAT)
		printf("%lli %i is eating\n", time, philo->id + 1);
	else if (status == SLEEP)
		printf("%lli %i is sleeping\n", time, philo->id + 1);
	else
		printf("%lli %i is thinking\n", time, philo->id + 1);
	pthread_mutex_unlock(&philo->total->print_mutex);
	return (1);
}
