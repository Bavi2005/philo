/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpichyal <bpichyal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:12:20 by bpichyal          #+#    #+#             */
/*   Updated: 2025/11/12 17:12:47 by bpichyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	validate_args(int ac, char **av)
{
	int	i;
	int	j;

	if (ac < 5 || ac > 6)
		return (1);
	i = 1;
	while (i < ac)
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] < '0' || av[i][j] > '9')
				return (1);
			j++;
		}
		if (ft_atoi(av[i]) <= 0)
			return (1);
		i++;
	}
	return (0);
}

static void	init_child(t_data *data, int i)
{
	data->philo_id = i + 1;
	data->last_eat_time = data->start_time;
	data->eat_count = 0;
	philo_routine(data);
}

static void	create_philosophers(t_data *data)
{
	int		i;
	pid_t	pid;

	data->pids = malloc(sizeof(pid_t) * data->num_philos);
	if (!data->pids)
		return ;
	i = 0;
	data->start_time = get_time();
	while (i < data->num_philos)
	{
		pid = fork();
		if (pid < 0)
			return (kill_all_philos(data));
		if (pid == 0)
			init_child(data, i);
		data->pids[i] = pid;
		i++;
	}
}

static void	wait_for_philosophers(t_data *data)
{
	int	i;
	int	status;

	i = 0;
	while (i < data->num_philos)
	{
		waitpid(-1, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) == 1)
		{
			kill_all_philos(data);
			break ;
		}
		i++;
	}
}

int	main(int ac, char **av)
{
	t_data	data;

	if (validate_args(ac, av))
	{
		printf("Error: Invalid arguments\n");
		return (1);
	}
	if (init_data(&data, ac, av))
	{
		printf("Error: Initialization failed\n");
		return (1);
	}
	create_philosophers(&data);
	wait_for_philosophers(&data);
	cleanup_semaphores(&data);
	if (data.pids)
		free(data.pids);
	return (0);
}
