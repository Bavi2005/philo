/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpichyal <bpichyal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 00:00:00 by bpichyal          #+#    #+#             */
/*   Updated: 2026/04/25 00:00:00 by bpichyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	take_forks(t_philo *philo)
{
	if (philo->data->num_philos == 1)
	{
		sem_wait(philo->left_fork);
		print_status(philo, "has taken a fork");
		return ;
	}
	if (philo->id % 2 == 0)
	{
		sem_wait(philo->right_fork);
		print_status(philo, "has taken a fork");
		sem_wait(philo->left_fork);
		print_status(philo, "has taken a fork");
	}
	else
	{
		sem_wait(philo->left_fork);
		print_status(philo, "has taken a fork");
		sem_wait(philo->right_fork);
		print_status(philo, "has taken a fork");
	}
}

static void	drop_forks(t_philo *philo)
{
	if (philo->data->num_philos == 1)
	{
		sem_post(philo->left_fork);
		return ;
	}
	sem_post(philo->left_fork);
	sem_post(philo->right_fork);
}

static void	philo_eat(t_philo *philo)
{
	take_forks(philo);
	if (philo->data->num_philos == 1)
		while (1)
			usleep(500);
	pthread_mutex_lock(&philo->meal_mutex);
	philo->last_meal = get_time_ms();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->meal_mutex);
	print_status(philo, "is eating");
	precise_sleep(philo->data->time_to_eat);
	drop_forks(philo);
}

void	philo_routine(t_philo *philo)
{
	while (1)
	{
		philo_eat(philo);
		if (enough_meals(philo))
			return ;
		print_status(philo, "is sleeping");
		precise_sleep(philo->data->time_to_sleep);
		philo_think(philo);
	}
}
