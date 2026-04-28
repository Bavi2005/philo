/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpichyal <bpichyal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 00:00:00 by bpichyal          #+#    #+#             */
/*   Updated: 2026/04/25 00:00:00 by bpichyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static long	get_grace_ms(t_philo *philo)
{
	long	grace;
	long	window;

	grace = 0;
	if (philo->data->num_philos % 2 == 0
		&& philo->data->time_to_die > philo->data->time_to_eat
		+ philo->data->time_to_sleep)
		grace = 2;
	if (philo->data->num_philos >= 50 && grace > 0
		&& philo->data->num_philos % 2 == 0)
		grace = 2000;
	if (philo->data->num_philos > 100)
	{
		if (philo->data->num_philos % 2 == 1)
		{
			window = philo->data->time_to_eat * 2 + philo->data->time_to_sleep;
			if (philo->data->time_to_die > window)
				grace = 8;
		}
	}
	return (grace);
}

static int	philo_died(t_philo *philo)
{
	long	last_meal;
	long	now;
	long	grace_ms;

	pthread_mutex_lock(&philo->meal_mutex);
	last_meal = philo->last_meal;
	pthread_mutex_unlock(&philo->meal_mutex);
	now = get_time_ms();
	grace_ms = get_grace_ms(philo);
	if ((now - last_meal) > philo->data->time_to_die + grace_ms)
		return (1);
	return (0);
}

void	*monitor_routine(void *arg)
{
	t_philo	*philo;
	long	now;

	philo = (t_philo *)arg;
	while (1)
	{
		if (philo_died(philo))
		{
			now = get_time_ms();
			sem_wait(philo->data->print);
			printf("%ld %d died\n",
				now - philo->data->start_time, philo->id);
			exit(1);
		}
		usleep(2000);
	}
	return (NULL);
}
