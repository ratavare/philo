/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ratavare <ratavare@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/11 17:10:03 by ratavare          #+#    #+#             */
/*   Updated: 2023/11/27 15:21:06 by ratavare         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char **av)
{
	static t_data	data;

	if (get_values(ac, av, &data))
		return (ft_error("Invalid Arguments.\n", EXIT_FAILURE));
	if (init(&data))
		return (ft_error("Fatal error while initializing semaphores.\n", \
		EXIT_FAILURE));
	if (philosophers(&data))
		return (ft_error("Fatal error initializing processes. \n", \
		EXIT_FAILURE));
	return (0);
}
