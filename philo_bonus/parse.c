/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpichyal <bpichyal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 00:00:00 by bpichyal          #+#    #+#             */
/*   Updated: 2026/04/25 00:00:00 by bpichyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static int	set_required_values(t_data *data, char **av)
{
	data->num_philos = ft_atoi_pos(av[1]);
	data->time_to_die = ft_atoi_pos(av[2]);
	data->time_to_eat = ft_atoi_pos(av[3]);
	data->time_to_sleep = ft_atoi_pos(av[4]);
	if (data->num_philos <= 0 || data->time_to_die <= 0
		|| data->time_to_eat <= 0 || data->time_to_sleep <= 0)
		return (1);
	return (0);
}

int	parse_args(t_data *data, int ac, char **av)
{
	if (ac != 5 && ac != 6)
		return (1);
	if (set_required_values(data, av))
		return (1);
	data->must_eat_count = -1;
	if (ac == 6)
	{
		data->must_eat_count = ft_atoi_pos(av[5]);
		if (data->must_eat_count <= 0)
			return (1);
	}
	return (0);
}
