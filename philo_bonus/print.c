/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpichyal <bpichyal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 00:00:00 by bpichyal          #+#    #+#             */
/*   Updated: 2026/04/25 00:00:00 by bpichyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	print_status(t_philo *philo, char *status)
{
	long	timestamp;

	sem_wait(philo->data->print);
	timestamp = get_time_ms() - philo->data->start_time;
	printf("%ld %d %s\n", timestamp, philo->id, status);
	sem_post(philo->data->print);
}
