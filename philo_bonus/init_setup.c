/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_setup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpichyal <bpichyal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 00:00:00 by bpichyal          #+#    #+#             */
/*   Updated: 2026/04/25 00:00:00 by bpichyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	init_pids(t_data *data)
{
	int	i;

	data->pids = malloc(sizeof(pid_t) * data->num_philos);
	if (!data->pids)
		return (1);
	i = 0;
	while (i < data->num_philos)
	{
		data->pids[i] = -1;
		i++;
	}
	return (0);
}

int	alloc_fork_arrays(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(sem_t *) * data->num_philos);
	data->fork_names = malloc(sizeof(char *) * data->num_philos);
	if (!data->forks || !data->fork_names)
		return (1);
	i = 0;
	while (i < data->num_philos)
	{
		data->forks[i] = NULL;
		data->fork_names[i] = NULL;
		i++;
	}
	return (0);
}

int	open_global_sems(t_data *data)
{
	sem_unlink(SEM_PRINT);
	sem_unlink(SEM_START);
	data->print = sem_open(SEM_PRINT, O_CREAT, 0644, 1);
	if (data->print == SEM_FAILED)
		return (data->print = NULL, 1);
	data->start = sem_open(SEM_START, O_CREAT, 0644, 0);
	if (data->start == SEM_FAILED)
		return (data->start = NULL, sem_close(data->print),
			data->print = NULL, 1);
	return (0);
}

static int	open_one_fork(t_data *data, int i)
{
	data->fork_names[i] = malloc(48);
	if (!data->fork_names[i])
		return (1);
	snprintf(data->fork_names[i], 48, "%s%d", SEM_FORK_PREFIX, i);
	sem_unlink(data->fork_names[i]);
	data->forks[i] = sem_open(data->fork_names[i], O_CREAT, 0644, 1);
	if (data->forks[i] == SEM_FAILED)
		return (data->forks[i] = NULL, 1);
	return (0);
}

int	open_forks(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (open_one_fork(data, i))
			return (1);
		i++;
	}
	return (0);
}
