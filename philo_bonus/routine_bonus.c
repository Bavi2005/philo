/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpichyal <bpichyal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:12:43 by bpichyal          #+#    #+#             */
/*   Updated: 2025/11/12 17:12:44 by bpichyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	philo_eat(t_data *data)
{
	sem_wait(data->forks);
	print_status(data, "has taken a fork");
	if (data->num_philos == 1)
	{
		ft_usleep(data->time_to_die + 10);
		sem_post(data->forks);
		exit(1);
	}
	sem_wait(data->forks);
	print_status(data, "has taken a fork");
	sem_wait(data->meal_sem);
	data->last_eat_time = get_time();
	data->eat_count++;
	sem_post(data->meal_sem);
	print_status(data, "is eating");
	ft_usleep(data->time_to_eat);
	sem_post(data->forks);
	sem_post(data->forks);
}

static void	philo_sleep(t_data *data)
{
	print_status(data, "is sleeping");
	ft_usleep(data->time_to_sleep);
}

static void	philo_think(t_data *data)
{
	print_status(data, "is thinking");
	usleep(200);
}

static int	check_finished(t_data *data)
{
	int	finished;

	finished = 0;
	sem_wait(data->meal_sem);
	if (data->must_eat_count != -1
		&& data->eat_count >= data->must_eat_count)
		finished = 1;
	sem_post(data->meal_sem);
	return (finished);
}

void	philo_routine(t_data *data)
{
	pthread_create(&data->monitor_thread, NULL, monitor_death, data);
	pthread_detach(data->monitor_thread);
	if (data->philo_id % 2 == 0)
		ft_usleep(data->time_to_eat);
	while (1)
	{
		philo_eat(data);
		if (check_finished(data))
			exit(0);
		philo_sleep(data);
		philo_think(data);
	}
}
