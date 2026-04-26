/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpichyal <bpichyal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 00:00:00 by bpichyal          #+#    #+#             */
/*   Updated: 2026/04/25 00:00:00 by bpichyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	close_forks(t_data *data)
{
	int	i;

	i = 0;
	while (data->forks && i < data->num_philos)
	{
		if (data->forks[i])
			sem_close(data->forks[i]);
		i++;
	}
}

static void	unlink_forks(t_data *data)
{
	int	i;

	i = 0;
	while (data->fork_names && i < data->num_philos)
	{
		if (data->fork_names[i])
		{
			sem_unlink(data->fork_names[i]);
			free(data->fork_names[i]);
		}
		i++;
	}
}

int	init_data(t_data *data)
{
	data->start_time = 0;
	if (init_pids(data) || alloc_fork_arrays(data)
		|| open_global_sems(data) || open_forks(data))
	{
		cleanup_data(data);
		return (1);
	}
	return (0);
}

void	cleanup_data(t_data *data)
{
	close_forks(data);
	unlink_forks(data);
	if (data->forks)
		free(data->forks);
	if (data->fork_names)
		free(data->fork_names);
	if (data->print)
		sem_close(data->print);
	if (data->start)
		sem_close(data->start);
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_START);
	if (data->pids)
		free(data->pids);
}
