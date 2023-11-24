/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:02:51 by ratavare          #+#    #+#             */
/*   Updated: 2023/11/24 16:23:20 by ratavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_values(int ac, char **av, t_data *data)
{
	if (!check_args(ac, av))
		return (1);
	data->philo_num = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->max_meals = ft_atoi(av[5]);
	else
		data->max_meals = INT_MAX;
	data->dead_flag = 0;
	if (data->philo_num > 250)
		return (1);
	return (0);
}

int	init_mutex(t_data *data)
{
	int	i;

	i = data->philo_num;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(data->forks[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(data->writing), NULL))
		return (1);
	if (pthread_mutex_init(&(data->death_check), NULL))
		return (1);
	return (0);
}

int	init_philos(t_data *data)
{
	int	i;

	i = data->philo_num;
	while (--i >= 0)
	{
		data->philosophers[i].id = i;
		data->philosophers[i].eat_count = 0;
		data->philosophers[i].left_fork_id = i;
		if (data->philo_num != 1)
		{
			if (i == data->philo_num - 1)
				data->philosophers[i].right_fork_id = 0;
			else
				data->philosophers[i].right_fork_id = i + 1;
		}
		data->philosophers[i].data = data;
	}
	return (0);
}

int	init(t_data *data)
{
	if (init_mutex(data))
		return (1);
	init_philos(data);
	return (0);
}
