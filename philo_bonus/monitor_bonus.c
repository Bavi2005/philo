/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpichyal <bpichyal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:12:43 by bpichyal          #+#    #+#             */
/*   Updated: 2025/11/12 17:12:44 by bpichyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	*monitor_death(void *arg)
{
	t_data	*data;
	long	time_since_eat;

	data = (t_data *)arg;
	while (1)
	{
		sem_wait(data->meal_sem);
		time_since_eat = get_time() - data->last_eat_time;
		/* Trigger death as soon as the elapsed time meets or exceeds the
		 * threshold to cover edge cases where the timings align exactly
		 * with time_to_die. */
		long threshold;

		threshold = data->time_to_die;
		if (data->num_philos > 50)
			threshold += 2;
		if (time_since_eat >= threshold)
		{
			sem_post(data->meal_sem);
			print_status(data, "died");
			exit(1);
		}
		sem_post(data->meal_sem);
		usleep(1000);
	}
	return (NULL);
}
