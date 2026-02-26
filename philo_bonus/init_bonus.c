/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpichyal <bpichyal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:12:43 by bpichyal          #+#    #+#             */
/*   Updated: 2025/11/12 17:12:44 by bpichyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	unlink_semaphores(void)
{
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_DEAD);
	sem_unlink(SEM_MEAL);
}

static int	open_semaphores(t_data *data)
{
	unlink_semaphores();
	data->forks = sem_open(SEM_FORKS, O_CREAT, 0644, data->num_philos);
	if (data->forks == SEM_FAILED)
		return (1);
	data->print_sem = sem_open(SEM_PRINT, O_CREAT, 0644, 1);
	if (data->print_sem == SEM_FAILED)
		return (1);
	data->dead_sem = sem_open(SEM_DEAD, O_CREAT, 0644, 0);
	if (data->dead_sem == SEM_FAILED)
		return (1);
	data->meal_sem = sem_open(SEM_MEAL, O_CREAT, 0644, 1);
	if (data->meal_sem == SEM_FAILED)
		return (1);
	return (0);
}

int	init_data(t_data *data, int ac, char **av)
{
	data->num_philos = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->must_eat_count = ft_atoi(av[5]);
	else
		data->must_eat_count = -1;
	data->philo_id = 0;
	data->eat_count = 0;
	data->last_eat_time = 0;
	data->pids = NULL;
	data->start_time = 0;
	if (open_semaphores(data))
		return (1);
	return (0);
}

void	cleanup_semaphores(t_data *data)
{
	if (data->forks != SEM_FAILED)
		sem_close(data->forks);
	if (data->print_sem != SEM_FAILED)
		sem_close(data->print_sem);
	if (data->dead_sem != SEM_FAILED)
		sem_close(data->dead_sem);
	if (data->meal_sem != SEM_FAILED)
		sem_close(data->meal_sem);
	unlink_semaphores();
}

void	kill_all_philos(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (data->pids[i] > 0)
			kill(data->pids[i], SIGKILL);
		i++;
	}
}
