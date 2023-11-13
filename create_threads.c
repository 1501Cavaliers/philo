/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:13:42 by flavian           #+#    #+#             */
/*   Updated: 2023/11/12 13:52:02 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	join_thread(t_data *data, int i)
{
	t_philo	*philo;

	philo = data->philo;
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(philo->id, NULL) != 0)
			return (2);
		philo = philo->next;
		i++;
	}
	if (pthread_join(data->check, NULL) != 0)
		return (2);
	return (0);
}

int	init_thread_2(t_data *data, int i)
{
	t_philo	*philo;

	usleep(2000);
	philo = data->philo;
	i = 0;
	while (i < data->nb_philo)
	{
		if (philo->data->nb_philo % 2 == 0 && philo->name % 2 == 1)
		{
			if (pthread_create(&philo->id, NULL, &dinner, philo) != 0)
				return (1);
		}
		else if (philo->data->nb_philo % 2 == 1 && philo->name % 2 == 0)
		{
			if (pthread_create(&philo->id, NULL, &dinner, philo) != 0)
				return (1);
		}
		philo = philo->next;
		i++;
	}
	if (pthread_create(&data->check, NULL, &funeral, data->philo) != 0)
		return (1);
	return (0);
}

int	create_thread(t_data *data)
{
	int		i;
	t_philo	*philo;

	if (!data->philo)
		return (1);
	philo = data->philo;
	i = 0;
	while (i < data->nb_philo)
	{
		if (philo->data->nb_philo % 2 == 0 && philo->name % 2 == 0)
		{
			if (pthread_create(&philo->id, NULL, &dinner, philo) != 0)
				return (1);
		}
		else if (philo->data->nb_philo % 2 == 1 && philo->name % 2 == 1)
		{
			if (pthread_create(&philo->id, NULL, &dinner, philo) != 0)
				return (1);
		}
		philo = philo->next;
		i++;
	}
	init_thread_2(data, i);
	return (join_thread(data, i));
}

int	check_init_philo(t_data *data, int val)
{
	if (!init_philo(data))
	{
		free_all(data, val);
		return (1);
	}
	return (0);
}
