/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:22:00 by ratavare          #+#    #+#             */
/*   Updated: 2023/11/21 16:17:13 by ratavare         ###   ########.fr       */
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
