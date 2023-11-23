/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:22:00 by ratavare          #+#    #+#             */
/*   Updated: 2023/11/23 20:04:39 by ratavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(const char *nptr)
{
	size_t	res;
	size_t	sinal;
	int		i;

	res = 0;
	sinal = 1;
	i = 0;
	while (nptr[i] == 32 || (nptr[i] >= 9 && nptr[i] <= 13))
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sinal *= -1;
		i++;
	}
	while ((nptr[i]))
	{
		if (!(nptr[i] >= '0' && nptr[i] <= '9'))
			return (0);
		res = 10 * res + nptr[i] - '0';
		i++;
	}
	return ((int)(res * sinal));
}

int	ft_error(const char *msg, int exit_code)
{
	while (*msg)
		write(2, msg++, 1);
	return (exit_code);
}

void	print_action(int id, t_data *data, char *msg)
{
	pthread_mutex_lock(&data->writing);
	if (!data->dead_flag)
	{
		printf("%lli ", get_time() - data->first_time);
		printf("%d %s\n", id, msg);
	}
	pthread_mutex_unlock(&data->writing);
}

int	check_dead_flag(t_data *data)
{
	int val;

	pthread_mutex_lock(&data->death_check);
	val = data->dead_flag;
	pthread_mutex_unlock(&data->death_check);
	return (val);
}