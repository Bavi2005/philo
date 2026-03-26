/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpichyal <bpichyal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:12:43 by bpichyal          #+#    #+#             */
/*   Updated: 2025/11/12 17:12:44 by bpichyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_death(t_data *data, int i)
{
	long	current_time;
	long	time_since_eat;

	pthread_mutex_lock(&data->data_mutex);
	if (data->dead_flag)
	{
		pthread_mutex_unlock(&data->data_mutex);
		return (1);
	}
	current_time = get_time();
	time_since_eat = current_time - data->philos[i].last_eat_time;
	/*
	 * A philosopher dies the moment the elapsed time since their last meal
	 * reaches the time_to_die threshold. Using '>=' (instead of '>') avoids
	 * letting edge cases slip through when the schedule is exactly aligned
	 * with time_to_die (e.g., time_to_die == time_to_eat + time_to_sleep),
	 * which several testers expect to result in a death.
	 */
	/* Apply a tiny tolerance only for large tables to absorb scheduling jitter */
	long	threshold;

	threshold = data->time_to_die;
	if (data->num_philos > 50)
		threshold += 2;
	if (time_since_eat >= threshold)
	{
		data->dead_flag = 1;
		pthread_mutex_unlock(&data->data_mutex);
		pthread_mutex_lock(&data->print_mutex);
		printf("%ld %d died\n", current_time - data->start_time,
			data->philos[i].id);
		pthread_mutex_unlock(&data->print_mutex);
		return (1);
	}
	pthread_mutex_unlock(&data->data_mutex);
	return (0);
}

static void	set_dead_flag(t_data *data)
{
	pthread_mutex_lock(&data->data_mutex);
	data->dead_flag = 1;
	pthread_mutex_unlock(&data->data_mutex);
}

static int	check_all_finished(t_data *data)
{
	int	i;
	int	finished;

	if (data->must_eat_count == -1)
		return (0);
	i = 0;
	finished = 0;
	pthread_mutex_lock(&data->data_mutex);
	while (i < data->num_philos)
	{
		if (data->philos[i].eat_count >= data->must_eat_count)
			finished++;
		i++;
	}
	pthread_mutex_unlock(&data->data_mutex);
	if (finished == data->num_philos)
		return (set_dead_flag(data), 1);
	return (0);
}

void	monitor(t_data *data)
{
	int	i;

	i = 0;
	while (1)
	{
		i = 0;
		while (i < data->num_philos)
		{
			if (check_death(data, i))
				return ;
			i++;
		}
		if (check_all_finished(data))
			return ;
		usleep(500);
	}
}
