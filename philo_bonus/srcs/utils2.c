/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:45:51 by ratavare          #+#    #+#             */
/*   Updated: 2023/12/04 17:49:53 by ratavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	handle_one_philo(int id, t_data *data)
{
	print_action(id, data, "has taken a fork");
	ft_mssleep(data->time_to_die);
	print_action(id, data, "died");
}

int	ft_abs(int nbr)
{
	if (nbr >= 0)
		return (nbr);
	else
		return (-nbr);
}

void	close_sems(t_data *data)
{
	sem_close(data->forks);
	sem_close(data->writing);
	sem_close(data->death_check);
}
