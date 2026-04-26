/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpichyal <bpichyal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 00:00:00 by bpichyal          #+#    #+#             */
/*   Updated: 2026/04/25 00:00:00 by bpichyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	init_philo(t_philo *philo, t_data *data, int id)
{
	philo->id = id;
	philo->eat_count = 0;
	philo->last_meal = data->start_time;
	philo->data = data;
	philo->left_fork = data->forks[id - 1];
	philo->right_fork = data->forks[id % data->num_philos];
}

static void	initial_delay(t_data *data, int id)
{
	if (data->num_philos <= 1 || id % 2 != 0)
		return ;
	precise_sleep(1);
}

void	child_process(t_data *data, int id)
{
	t_philo	philo;

	sem_wait(data->start);
	data->start_time = get_time_ms();
	init_philo(&philo, data, id);
	if (pthread_mutex_init(&philo.meal_mutex, NULL))
		exit(1);
	if (pthread_create(&philo.monitor, NULL, monitor_routine, &philo))
		exit(1);
	pthread_detach(philo.monitor);
	initial_delay(data, id);
	philo_routine(&philo);
	exit(0);
}
