/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpichyal <bpichyal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 00:00:00 by bpichyal          #+#    #+#             */
/*   Updated: 2026/04/25 00:00:00 by bpichyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	kill_all(t_data *data)
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

static int	create_child(t_data *data, int i)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (1);
	if (pid == 0)
		child_process(data, i + 1);
	data->pids[i] = pid;
	return (0);
}

int	launch_processes(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (create_child(data, i))
		{
			kill_all(data);
			return (1);
		}
		i++;
	}
	i = 0;
	while (i < data->num_philos)
	{
		sem_post(data->start);
		i++;
	}
	return (0);
}

void	wait_processes(t_data *data)
{
	int		status;
	int		finished;
	pid_t	pid;

	finished = 0;
	while (finished < data->num_philos)
	{
		pid = waitpid(-1, &status, 0);
		if (pid < 0)
			break ;
		if (WIFEXITED(status) && WEXITSTATUS(status) == 0)
			finished++;
		else
		{
			kill_all(data);
			break ;
		}
	}
	while (waitpid(-1, &status, 0) > 0)
		;
}
