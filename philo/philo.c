/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpichyal <bpichyal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:12:20 by bpichyal          #+#    #+#             */
/*   Updated: 2025/11/12 17:12:47 by bpichyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

static void	start_simulation(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->num_philos)
	{
		if (pthread_create(&data->philos[i].thread, NULL,
				philo_routine, &data->philos[i]))
		{
			data->dead_flag = 1;
			break ;
		}
		i++;
	}
	monitor(data);
	i = 0;
	while (i < data->num_philos)
	{
		pthread_join(data->philos[i].thread, NULL);
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
	if (init_philos(&data))
	{
		cleanup(&data);
		printf("Error: Philosopher initialization failed\n");
		return (1);
	}
	start_simulation(&data);
	cleanup(&data);
	return (0);
}
