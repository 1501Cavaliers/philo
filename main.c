/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:16:24 by flavian           #+#    #+#             */
/*   Updated: 2023/11/01 12:24:55 by flavian          ###   ########.fr       */
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
	if (init_mutex(data))
		return (ft_error("Mutex init error", 2));
	if (init_philo(data))
		return (ft_error("Philo init error", 3));
	if (init_thread(data))
		return (ft_error("Thread init error", 4));
}