/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:18:35 by ratavare          #+#    #+#             */
/*   Updated: 2023/12/04 21:43:33 by ratavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/wait.h>

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

struct s_philo
{
	pthread_t		super;
	int				id;
	pid_t			pid;
	int				eat_count;
	long long		last_meal;
	t_data			*data;
};

struct s_data
{
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				max_meals;
	long long		first_time;
	int				dead_flag;
	sem_t			*death_check;
	sem_t			*forks;
	sem_t			*writing;
	sem_t			*death_write;
	t_philo			philosophers[250];
};

// check.c
int					check_args(int ac, char **av);

// init.c
int					get_values(int ac, char **av, t_data *data);
int					init_semaphore(t_data *data);
int					init_philos(t_data *data);
int					init(t_data *data);

// utils.c
int					ft_atoi(const char *nptr);
int					ft_error(const char *msg, int exit_code);
void				print_action(int id, t_data *data, char *msg);
int					check_dead_flag(t_data *data);
int					check_if_all_ate(t_data *data, t_philo *philo);

// utils2.c
int					ft_abs(int nbr);
void				handle_one_philo(int id, t_data *data);
void				close_sems(t_data *data);

// time.c
void				ft_mssleep(int ms);
unsigned long long	get_time(void);

// philo.c
int					philosophers(t_data *data);

#endif