/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:48:30 by ratavare          #+#    #+#             */
/*   Updated: 2023/12/05 13:23:59 by ratavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo, t_data *data)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(&data->forks[philo->left_fork_id]);
		print_action(philo->id, data, "has taken a fork"); 
		pthread_mutex_lock(&data->forks[philo->right_fork_id]);
		print_action(philo->id, data, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(&data->forks[philo->right_fork_id]);
		print_action(philo->id, data, "has taken a fork");
		pthread_mutex_lock(&data->forks[philo->left_fork_id]);
		print_action(philo->id, data, "has taken a fork"); 
	}
	print_action(philo->id, data, "is eating");
	pthread_mutex_lock(&data->death_check);
	philo->last_meal = get_time();
	philo->eat_count++;
	pthread_mutex_unlock(&data->death_check);
	ft_mssleep(data->time_to_eat);
	pthread_mutex_unlock(&data->forks[philo->right_fork_id]);
	pthread_mutex_unlock(&data->forks[philo->left_fork_id]);
}

void	*routine(void *v_philo)
{
	t_philo	*philo;
	t_data	*data;

	philo = (t_philo *)v_philo;
	data = philo->data;
	if (data->philo_num == 1)
		return (print_action(philo->id, data, "has taken a fork"), NULL);
	while (!check_dead_flag(data))
	{
		eating(philo, data);
		if (philo->eat_count == data->max_meals)
			break ;
		print_action(philo->id, data, "is sleeping");
		ft_mssleep(data->time_to_sleep);
		print_action(philo->id, data, "is thinking");
		ft_mssleep(ft_abs(data->time_to_eat - data->time_to_sleep));
		usleep(500);
	}
	return (NULL);
}

void	supervisor(t_philo *philo, t_data *data)
{
	int	i;

	while (!check_dead_flag(data))
	{
		i = -1;
		while (++i < data->philo_num && !check_dead_flag(data))
		{
			if (check_if_all_ate(data, philo))
				return ;
			pthread_mutex_lock(&data->death_check);
			if (get_time() - philo[i].last_meal >= \
			(long long unsigned int)data->time_to_die)
			{
				print_action(i, data, "died");
				pthread_mutex_lock(&data->writing);
				data->dead_flag = 1;
				pthread_mutex_unlock(&data->writing);
				pthread_mutex_unlock(&data->death_check);
				return ;
			}
			else
				pthread_mutex_unlock(&data->death_check);
		}
	}
}

void	destroy(t_philo *philo, t_data *data)
{
	int	i;

	i = 0;
	while (i < data->philo_num)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < data->philo_num)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&data->writing);
	pthread_mutex_destroy(&data->death_check);
}

int	philosophers(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = data->philo_num;
	philo = data->philosophers;
	data->first_time = get_time();
	while (--i >= 0)
	{
		if (pthread_create(&(philo[i].thread), NULL, routine, &(philo[i])))
			return (1);
		pthread_mutex_lock(&data->death_check);
		philo[i].last_meal = get_time();
		pthread_mutex_unlock(&data->death_check);
	}
	supervisor(philo, data);
	destroy(philo, data);
	return (0);
}
