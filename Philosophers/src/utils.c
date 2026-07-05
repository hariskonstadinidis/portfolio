/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hariskon <hariskon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/19 20:50:31 by hkonstan          #+#    #+#             */
/*   Updated: 2026/02/25 14:30:19 by hariskon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

long long	get_time(long long start_time)
{
	struct timeval	t;
	long long		c_time;
	long long		sim_time;

	gettimeofday(&t, NULL);
	c_time = t.tv_sec * 1000 + t.tv_usec / 1000;
	sim_time = c_time - start_time;
	return (sim_time);
}

int	check_state(t_state state)
{
	if (state == DEAD)
		return (0);
	else if (state == FED)
		return (0);
	else
		return (1);
}

void	ft_usleep(t_philo *philo, long long duration)
{
	long long	start;
	long long	remaining;

	(void)philo;
	start = get_time(0);
	while (1)
	{
		remaining = start + duration - get_time(0);
		if (remaining <= 0)
			break ;
		if (remaining > 2)
			usleep(500);
		else
			usleep(100);
	}
}

void	change_state(t_total *total, int i)
{
	pthread_mutex_lock(&total->state_mutex);
	total->state = DEAD;
	pthread_mutex_unlock(&total->state_mutex);
	pthread_mutex_lock(&total->print_mutex);
	printf("%lli %i died\n", get_time(total->time),
		total->philosophers[i].id + 1);
	pthread_mutex_unlock(&total->print_mutex);
	pthread_mutex_unlock(&total->philosophers[i].eat_mutex);
}
