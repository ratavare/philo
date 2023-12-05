/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:02:51 by ratavare          #+#    #+#             */
/*   Updated: 2023/12/05 13:08:54 by ratavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_values(int ac, char **av, t_data *data)
{
	if (!check_args(ac, av))
		return (1);
	data->philo_num = ft_atoi(av[1]);
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

int	init_semaphore(t_data *data)
{
	sem_unlink("/forks");
	sem_unlink("/writing");
	sem_unlink("/death_check");
	data->forks = sem_open("/forks", O_CREAT, S_IRWXU, data->philo_num);
	data->writing = sem_open("/writing", O_CREAT, S_IRWXU, 1);
	data->death_check = sem_open("/death_check", O_CREAT, S_IRWXU, 1);
	if (data->forks == SEM_FAILED || data->writing == SEM_FAILED || \
	data->death_check == SEM_FAILED)
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
		data->philosophers[i].data = data;
	}
	return (0);
}

int	init(t_data *data)
{
	data->sems = 1;
	if (init_semaphore(data))
		return (1);
	init_philos(data);
	return (0);
}
