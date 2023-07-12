/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:02:51 by ratavare          #+#    #+#             */
/*   Updated: 2023/07/12 17:43:00 by ratavare         ###   ########.fr       */
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

t_philo	philo_list_init(t_data *data)
{
	int		i;
	t_philo	*philo;

	i = 1;
	while (i < data->philo_num)
	{
		if (data->first_seat == NULL)
			data->first_seat = philo;
	}
}
