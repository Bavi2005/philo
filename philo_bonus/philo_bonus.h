/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bpichyal <bpichyal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 00:00:00 by bpichyal          #+#    #+#             */
/*   Updated: 2026/04/25 00:00:00 by bpichyal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# define SEM_PRINT "/philo_bonus_print"
# define SEM_START "/philo_bonus_start"
# define SEM_FORK_PREFIX "/philo_bonus_fork_"

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <fcntl.h>
# include <signal.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>

typedef struct s_data						t_data;
typedef struct s_philo						t_philo;

struct s_data
{
	int				num_philos;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				must_eat_count;
	long			start_time;
	pid_t			*pids;
	sem_t			**forks;
	char			**fork_names;
	sem_t			*print;
	sem_t			*start;
};

struct s_philo
{
	int				id;
	int				eat_count;
	long			last_meal;
	pthread_t		monitor;
	pthread_mutex_t	meal_mutex;
	t_data			*data;
	sem_t			*left_fork;
	sem_t			*right_fork;
};

int				parse_args(t_data *data, int ac, char **av);
int				init_data(t_data *data);
void			cleanup_data(t_data *data);
int				init_pids(t_data *data);
int				alloc_fork_arrays(t_data *data);
int				open_global_sems(t_data *data);
int				open_forks(t_data *data);
int				launch_processes(t_data *data);
void			wait_processes(t_data *data);
void			kill_all(t_data *data);
void			child_process(t_data *data, int id);
void			philo_routine(t_philo *philo);
int				enough_meals(t_philo *philo);
void			philo_think(t_philo *philo);
void			*monitor_routine(void *arg);
void			print_status(t_philo *philo, char *status);
long			get_time_ms(void);
void			precise_sleep(long time_ms);
int				ft_atoi_pos(const char *str);

#endif