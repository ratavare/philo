/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:16:38 by ratavare          #+#    #+#             */
/*   Updated: 2023/07/11 17:39:02 by ratavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(int ac, char **av, t_data *data)
{
	int	i;

	i = 2;
	(void)data;
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