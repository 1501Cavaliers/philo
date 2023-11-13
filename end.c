/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:51:11 by fserpe            #+#    #+#             */
/*   Updated: 2023/11/12 13:37:55 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex_2(t_data *data, int val, int err, int i)
{
	if (err < val)
	{
		while (i < data->nb_philo && &data->philock[i])
		{
			if (pthread_mutex_destroy(&data->philock[i++]) != 0)
				return ;
			i++;
		}
		free(data->philock);
		err++;
	}
	if (err < val)
	{
		if (pthread_mutex_destroy(&data->write) != 0)
			return ;
		err++;
	}
	if (err < val)
	{
		if (pthread_mutex_destroy(&data->death) != 0)
			return ;
		err++;
	}
}

int	check_death(t_philo *philo)
{
	int	dying;

	pthread_mutex_lock(&philo->data->death);
	dying = *philo->is_dead;
	pthread_mutex_unlock(&philo->data->death);
	return (dying);
}

void	tumb(t_philo *philo, int philo_full)
{
	pthread_mutex_lock(&philo->data->death);
	*philo->is_dead = 1;
	pthread_mutex_unlock(&philo->data->death);
	if (philo_full != philo->data->nb_philo)
	{
		pthread_mutex_lock(&philo->data->write);
		printf("%ld %d is dead\n", curenttime(philo->start_time), philo->name);
		pthread_mutex_unlock(&philo->data->write);
	}
}

void	*funeral(void *data)
{
	t_philo	*philo;
	int		philo_full;

	philo_full = 0;
	philo = (t_philo *)data;
	while (philo && !check_death(philo))
	{
		pthread_mutex_lock(&philo->philock);
		if (philo->name == 1)
			philo_full = 0;
		if (philo->ate == philo->data->nb_eat)
			philo_full++;
		if ((philo->death_time < curenttime(philo->start_time)
				&& (philo->ate != philo->data->nb_eat))
			|| (philo_full == philo->data->nb_philo))
			tumb(philo, philo_full);
		pthread_mutex_unlock(&philo->philock);
		philo = philo->next;
	}
	return (NULL);
}
