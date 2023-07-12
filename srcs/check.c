/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:16:38 by ratavare          #+#    #+#             */
/*   Updated: 2023/07/12 16:28:38 by ratavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_values(int ac, char **av, t_data *data)
{
	if (!check_args(ac, av))
		return (0);
	data->philo_num = ft_atoi(av[1]);
	data->time_to_die = ft_atoi(av[2]);
	data->time_to_eat = ft_atoi(av[3]);
	data->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		data->total_meals = ft_atoi(av[5]);
	return (1);
}

int	check_args(int ac, char **av)
{
	int	i;

	i = 2;
	if (ac == 5 || ac == 6)
	{
		if (ft_atoi(av[1]) < 1)
			return (0);
		while (i < ac)
			if (ft_atoi(av[i++]) <= 0)
				return (0);
		return (1);
	}
	return (0);
}
