/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpichyal <bpichyal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 17:12:43 by bpichyal          #+#    #+#             */
/*   Updated: 2025/11/12 17:12:44 by bpichyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>
# include <semaphore.h>
# include <fcntl.h>

# define SEM_FORKS "/philo_forks"
# define SEM_PRINT "/philo_print"
# define SEM_DEAD "/philo_dead"
# define SEM_MEAL "/philo_meal"

typedef struct s_data
{
	int				num_philos;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	long			start_time;
	int				philo_id;
	int				eat_count;
	long			last_eat_time;
	pid_t			*pids;
	sem_t			*forks;
	sem_t			*print_sem;
	sem_t			*dead_sem;
	sem_t			*meal_sem;
	pthread_t		monitor_thread;
}	t_data;

int		ft_atoi(const char *str);
long	get_time(void);
void	ft_usleep(long time_ms);
void	print_status(t_data *data, char *status);
int		init_data(t_data *data, int ac, char **av);
void	cleanup_semaphores(t_data *data);
void	philo_routine(t_data *data);
void	kill_all_philos(t_data *data);
void	*monitor_death(void *arg);

#endif
