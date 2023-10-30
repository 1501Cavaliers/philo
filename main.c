/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:16:24 by flavian           #+#    #+#             */
/*   Updated: 2023/10/30 15:55:49 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_error(char *msg, int i)
{
	printf("%s\n", msg);
	return (i);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac < 5 || ac > 6)
		return (ft_error("Wrong number of arg", 0));
	data = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	if (!parsing(data, av))
		return (ft_error("Parsing error", 1));
	if (init_mutex(data) != 0)
		return (ft_error("Mutex init error", 2));
	init_philo(data);
}