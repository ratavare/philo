/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 16:48:30 by ratavare          #+#    #+#             */
/*   Updated: 2023/11/24 16:46:02 by ratavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo, t_data *data)
{
	if (philo->id % 2)
	{
		pthread_mutex_lock(&data->forks[philo->left_fork_id]);
		print_action(philo->id, data, "has taken a fork (his)"); 
		pthread_mutex_lock(&data->forks[philo->right_fork_id]);
		print_action(philo->id, data, "has taken a fork (right)");
	}
	else
	{
		pthread_mutex_lock(&data->forks[philo->right_fork_id]);
		print_action(philo->id, data, "has taken a fork (right)");
		pthread_mutex_lock(&data->forks[philo->left_fork_id]);
		print_action(philo->id, data, "has taken a fork (his)"); 
	}
	pthread_mutex_lock(&data->death_check);
	print_action(philo->id, data, "is eating");
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
	if (philo->id % 2)
		ft_mssleep(10);
	if (data->philo_num == 1)
		return (print_action(philo->id, data, "has taken a fork (his)"), NULL);
	while (!check_dead_flag(data))
	{
		// pthread_mutex_lock(&data->death_check);
		// if (!(data->dead_flag))
		// {
			// pthread_mutex_unlock(&data->death_check);
			eating(philo, data);
			if (philo->eat_count == data->max_meals)
				break ;
			print_action(philo->id, data, "is sleeping");
			ft_mssleep(data->time_to_sleep);
			print_action(philo->id, data, "is thinking");
		// }
		// else
			// pthread_mutex_unlock(&data->death_check);
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
				print_action(philo->id, data, "died");
				pthread_mutex_lock(&data->writing);
				data->dead_flag = 1;
				pthread_mutex_unlock(&data->writing);
				pthread_mutex_unlock(&data->death_check);
				return ;
			}
			else
				pthread_mutex_unlock(&data->death_check);
		}
		if (data->dead_flag)
			break ;
		// usleep(225);
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
	i = data->philo_num;
	while (i > 0)
	{
		pthread_mutex_destroy(&data->forks[i]);
		i--;
	}
	pthread_mutex_destroy(&data->writing);
	pthread_mutex_destroy(&data->death_check);
}

int	philosophers(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 0;
	data->first_time = get_time();
	philo = data->philosophers;
	while (i < data->philo_num)
	{
		if (pthread_create(&(philo[i].thread), NULL, routine, &(philo[i])))
			return (1);
		pthread_mutex_lock(&data->death_check);
		philo[i].last_meal = get_time();
		pthread_mutex_unlock(&data->death_check);
		i++;
	}
	supervisor(philo, data);
	destroy(philo, data);
	return (0);
}
