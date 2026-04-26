/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpichyal <bpichyal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 00:00:00 by bpichyal          #+#    #+#             */
/*   Updated: 2026/04/25 00:00:00 by bpichyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	enough_meals(t_philo *philo)
{
	int	done;

	if (philo->data->must_eat_count == -1)
		return (0);
	pthread_mutex_lock(&philo->meal_mutex);
	done = (philo->eat_count >= philo->data->must_eat_count);
	pthread_mutex_unlock(&philo->meal_mutex);
	return (done);
}

void	philo_think(t_philo *philo)
{
	long	think_time;
	long	window;

	print_status(philo, "is thinking");
	if (philo->data->num_philos % 2 == 1)
	{
		think_time = philo->data->time_to_eat * 2 - philo->data->time_to_sleep;
		window = philo->data->time_to_eat * 2 + philo->data->time_to_sleep;
		if (philo->data->time_to_die <= window)
			think_time++;
		else if (philo->data->time_to_die == window + 1 && think_time > 1)
			think_time -= 2;
		if (think_time > 0)
			precise_sleep(think_time);
	}
	else if (philo->data->time_to_die <= philo->data->time_to_eat
		+ philo->data->time_to_sleep)
		precise_sleep(1);
}
