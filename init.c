/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:53:53 by flavian           #+#    #+#             */
/*   Updated: 2023/11/02 17:20:25 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (1);
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i++], NULL) != 0)
			return (2);
	}
	data->philock = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->philock)
		return (1);
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->philock[i++], NULL) != 0)
			return (2);
	}
	if (pthread_mutex_init(&data->death, NULL) != 0)
		return (2);
	if (pthread_mutex_init(&data->write, NULL) != 0)
		return (2);
	return (0);
}

long	int	gettime()
{
	struct timeval x;
	gettimeofday(&x, NULL);
	return ((long int)x.tv_sec * 1000 + (long int)x.tv_usec / 1000);
}

t_philo	*create_philo(t_data *data, int name, int time)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->name = name;
	philo->start_time = time;
	philo->dying = 0;
	philo->ate = 0;
	philo->data = data;
	if (philo->name == 1)
	{
		philo->r_fork = &data->forks[name - 1];
		philo->l_fork = &data->forks[data->nb_philo - 1];
	}
	else
	{
		philo->r_fork = &data->forks[name - 2];
		philo->l_fork = &data->forks[name - 1];	
	}
	philo->philock = data->philock[name - 1];
	return (philo);
}

int	init_philo(t_data *data)
{
	t_philo *philo;
	long int time;
	int		i;

	i = 1;
	time = gettime();
	philo = create_philo(data, i, time);
	data->philo = philo;
	while (++i <= data->nb_philo)
	{
		philo->next = create_philo(data, i, time);
		philo = philo->next;
	}
	philo->next = NULL;
	return (0);
}