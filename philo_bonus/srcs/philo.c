/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:48:30 by ratavare          #+#    #+#             */
/*   Updated: 2023/11/29 18:04:29 by ratavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo, t_data *data)
{
	sem_wait(data->forks);
	print_action(philo->id, data, "has taken a fork"); 
	sem_wait(data->forks);
	print_action(philo->id, data, "has taken a fork");
	print_action(philo->id, data, "is eating");
	sem_wait(data->death_check);
	philo->last_meal = get_time();
	philo->eat_count++;
	sem_post(data->death_check);
	ft_mssleep(data->time_to_eat);
	sem_post(data->forks);
	sem_post(data->forks);
}

void	*supervisor(void *v_philo)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)v_philo;
	data = philo->data;
	while (1)
	{
		sem_wait(data->death_check);
		if (get_time() - philo->last_meal >= \
		(long long unsigned int)data->time_to_die)
		{
			print_action(philo->id, data, "died");
			sem_wait(data->writing);
			data->dead_flag = 1;
			sem_post(data->death_check);
			exit(1);
		}
		else
			sem_post(data->death_check);
		if (data->dead_flag || check_if_all_ate(data, philo))
			break ;
		usleep(1000);
	}
	return (NULL);
}

void	routine(t_philo *philo)
{
	t_data		*data;

	data = philo->data;
	philo->last_meal = get_time();
	pthread_create(&(philo->super), NULL, supervisor, philo);
	if (data->philo_num == 1)
		return (print_action(philo->id, data, "has taken a fork"));
	if (philo->id % 2)
		ft_mssleep(2);
	while (!check_dead_flag(data))
	{
		eating(philo, data);
		if (philo->eat_count == data->max_meals)
			break ;
		print_action(philo->id, data, "is sleeping");
		ft_mssleep(data->time_to_sleep);
		print_action(philo->id, data, "is thinking");
	}
	pthread_join(philo->super, NULL);
	if (data->dead_flag)
		exit(1);
	exit(0);
}

void	destroy(t_philo *philo, t_data *data)
{
	int	i;
	int	val;

	i = 0;
	while (i < data->philo_num)
	{
		waitpid(-1, &val, 0);
		if (val != 0)
		{
			i = 0;
			while (i < data->philo_num)
			{
				kill(philo[i].pid, SIGKILL);
				i++;
			}
			break ;
		}
		i++;
	}
	while (i < data->philo_num)
		kill(philo[i++].pid, SIGKILL);
	sem_close(data->forks);
	sem_close(data->writing);
	sem_close(data->death_check);
}

int	philosophers(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = -1;
	philo = data->philosophers;
	data->first_time = get_time();
	while (++i < data->philo_num)
	{
		philo[i].pid = fork();
		if (philo[i].pid < 0)
			return (1);
		if (philo[i].pid == 0)
			routine(&(philo[i]));
	}
	destroy(philo, data);
	return (0);
}
