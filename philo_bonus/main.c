/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpichyal <bpichyal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 00:00:00 by bpichyal          #+#    #+#             */
/*   Updated: 2026/04/25 00:00:00 by bpichyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	init_defaults(t_data *data)
{
	data->num_philos = 0;
	data->time_to_die = 0;
	data->time_to_eat = 0;
	data->time_to_sleep = 0;
	data->must_eat_count = -1;
	data->start_time = 0;
	data->pids = NULL;
	data->forks = NULL;
	data->fork_names = NULL;
	data->print = NULL;
	data->start = NULL;
}

int	main(int ac, char **av)
{
	t_data	data;

	init_defaults(&data);
	if (parse_args(&data, ac, av))
	{
		printf("Error: invalid arguments\n");
		return (1);
	}
	if (init_data(&data))
	{
		printf("Error: initialization failed\n");
		return (1);
	}
	if (launch_processes(&data))
	{
		cleanup_data(&data);
		printf("Error: failed to create processes\n");
		return (1);
	}
	wait_processes(&data);
	cleanup_data(&data);
	return (0);
}
