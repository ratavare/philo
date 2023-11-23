/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:18:35 by ratavare          #+#    #+#             */
/*   Updated: 2023/11/23 20:05:11 by ratavare         ###   ########.fr       */
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

/*

To do:

- Create threads and routines for the philosophers, keep in mind:
	. Saving the fisrt timestamp in order to compare times.
	. Creating accurate time comparison functions.
	. Preventing DeadLocks
	. Have them eat and print the right info inside their routine.

- Checker function to see if they have died.
- Destroying all Mutexes and Threads and exiting the program.

*/

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

struct s_philo
{
	pthread_t		thread;
	int				id;
	int				eat_count;
	int				left_fork_id;
	int				right_fork_id;
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
	pthread_mutex_t	death_check;
	pthread_mutex_t	forks[250];
	pthread_mutex_t	writing;
	t_philo			philosophers[250];
};

// check.c
int	check_args(int ac, char **av);

// init.c
int	get_values(int ac, char **av, t_data *data);
int	init_mutex(t_data *data);
int	init_philos(t_data *data);
int	init(t_data *data);

// utils.c
int	ft_atoi(const char *nptr);
int	ft_error(const char *msg, int exit_code);
void	print_action(int id, t_data *data, char *msg);
int	check_dead_flag(t_data *data);

// time.c
void				ft_mssleep(int ms);
unsigned long long	get_time(void);

// philo.c
int	philosophers(t_data *data);

#endif