/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpichyal <bpichyal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:12:43 by bpichyal          #+#    #+#             */
/*   Updated: 2025/11/12 17:12:44 by bpichyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check_dead(t_data *data)
{
	int	dead;

	pthread_mutex_lock(&data->data_mutex);
	dead = data->dead_flag;
	pthread_mutex_unlock(&data->data_mutex);
	return (dead);
}

static int	check_finished(t_philo *philo)
{
	int	finished;

	pthread_mutex_lock(&philo->data->data_mutex);
	if (philo->data->must_eat_count != -1
		&& philo->eat_count >= philo->data->must_eat_count)
		finished = 1;
	else
		finished = 0;
	pthread_mutex_unlock(&philo->data->data_mutex);
	return (finished);
}

static void	wait_all_ready(t_data *data)
{
	while (1)
	{
		pthread_mutex_lock(&data->data_mutex);
		if (data->all_ready)
		{
			pthread_mutex_unlock(&data->data_mutex);
			break ;
		}
		pthread_mutex_unlock(&data->data_mutex);
		usleep(50);
	}
}

static void	initial_delay(t_philo *philo)
{
	wait_all_ready(philo->data);
	if (philo->data->num_philos == 1)
		return ;
	if (philo->id % 2 == 0)
		ft_usleep(philo->data->time_to_eat / 2, philo->data);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	initial_delay(philo);
	while (!check_dead(philo->data))
	{
		philo_eat(philo);
		if (philo->data->num_philos == 1)
			break ;
		if (check_finished(philo) || check_dead(philo->data))
			break ;
		philo_sleep(philo);
		if (check_dead(philo->data))
			break ;
		philo_think(philo);
	}
	return (NULL);
}
