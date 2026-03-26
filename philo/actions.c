/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpichyal <bpichyal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:12:43 by bpichyal          #+#    #+#             */
/*   Updated: 2025/11/12 17:12:44 by bpichyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	take_forks(t_philo *philo)
{
	pthread_mutex_t	*first;
	pthread_mutex_t	*second;
 	int			locked;

	/* Single philosopher: grab the only fork and wait for death */
	if (philo->data->num_philos == 1)
	{
		pthread_mutex_lock(philo->left_fork);
		print_status(philo, "has taken a fork");
		return ;
	}
	/* Order forks consistently to avoid circular wait / starvation */
	if (philo->left_fork < philo->right_fork)
	{
		first = philo->left_fork;
		second = philo->right_fork;
	}
	else
	{
		first = philo->right_fork;
		second = philo->left_fork;
	}
	while (1)
	{
		pthread_mutex_lock(first);
		print_status(philo, "has taken a fork");
		locked = pthread_mutex_trylock(second);
		if (locked == 0)
		{
			print_status(philo, "has taken a fork");
			return ;
		}
		pthread_mutex_unlock(first);
		/* brief backoff to let neighbours progress */
		usleep(100);
		pthread_mutex_lock(&philo->data->data_mutex);
		if (philo->data->dead_flag)
		{
			pthread_mutex_unlock(&philo->data->data_mutex);
			return ;
		}
		pthread_mutex_unlock(&philo->data->data_mutex);
	}
}

static void	release_forks(t_philo *philo)
{
	if (philo->data->num_philos == 1)
	{
		pthread_mutex_unlock(philo->left_fork);
		return ;
	}
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	philo_eat(t_philo *philo)
{
	take_forks(philo);
	if (philo->data->num_philos == 1)
		return ;
	pthread_mutex_lock(&philo->data->data_mutex);
	philo->last_eat_time = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&philo->data->data_mutex);
	print_status(philo, "is eating");
	ft_usleep(philo->data->time_to_eat, philo->data);
	release_forks(philo);
}

void	philo_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep, philo->data);
}

void	philo_think(t_philo *philo)
{
	long	think_time;
	int		n;

	print_status(philo, "is thinking");
	n = philo->data->num_philos;
	if (n % 2 == 1)
	{
		think_time = (philo->data->time_to_eat * 2)
			- philo->data->time_to_sleep;
		if (think_time > 0)
			ft_usleep(think_time, philo->data);
	}
	else if (n > 100)
		usleep(100);
}
