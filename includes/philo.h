/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 16:18:35 by ratavare          #+#    #+#             */
/*   Updated: 2023/07/12 16:24:48 by ratavare         ###   ########.fr       */
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

# define DEAD	1
# define EAT	2
# define SLEEP	3
# define THINK	4
# define ALIVE	5

typedef struct s_data	t_data;
typedef struct s_philo	t_philo;

struct s_data
{
	unsigned int	start;
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				total_meals;
};

struct s_philo
{
	int				id;
	bool			fork;
	int				status;
	int				eat_count;
	pthread_mutex_t	mutex_status;
	pthread_mutex_t	mutex_fork;
	pthread_t		thread;
	t_philo			*next;
};

// check.c
int	get_values(int ac, char **av, t_data *data);
int	check_args(int ac, char **av);

//utils.c
int	ft_atoi(const char *nptr);

#endif