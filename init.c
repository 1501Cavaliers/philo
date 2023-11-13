/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 13:53:53 by flavian           #+#    #+#             */
/*   Updated: 2023/11/12 13:52:18 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_mutex_data_pt2(t_data *data, int i)
{
	data->philock = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->philock)
		return (-2);
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->philock[i++], NULL) != 0)
			return (2);
	}
	if (pthread_mutex_init(&data->write, NULL) != 0)
		return (3);
	if (pthread_mutex_init(&data->death, NULL) != 0)
		return (4);
	return (0);
}

int	init_mutex_data_pt1(t_data *data)
{
	int	i;

	i = 0;
	data->forks = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	if (!data->forks)
		return (-1);
	while (i < data->nb_philo)
	{
		if (pthread_mutex_init(&data->forks[i++], NULL) != 0)
			return (1);
	}
	return (init_mutex_data_pt2(data, i));
}

void	init_mutex_philo(t_data *data, t_philo *philo)
{
	if (philo->name == 1)
	{
		philo->r_fork = &data->forks[data->nb_philo - 1];
		philo->l_fork = &data->forks[philo->name - 1];
	}
	if (philo->name != 1)
	{
		philo->r_fork = &data->forks[philo->name - 2];
		philo->l_fork = &data->forks[philo->name - 1];
	}
	philo->philock = data->philock[philo->name - 1];
}

t_philo	*create_philo(t_data *data, int name, long int time)
{
	t_philo	*philo;

	philo = malloc(sizeof(t_philo));
	if (!philo)
		return (NULL);
	philo->name = name;
	philo->start_time = time;
	philo->death_time = data->tt_die;
	philo->is_dead = &data->is_dead;
	philo->ate = 0;
	philo->data = data;
	init_mutex_philo(data, philo);
	return (philo);
}

int	init_philo(t_data *data)
{
	t_philo		*philo;
	long int	time;
	int			i;

	i = 1;
	time = gettime();
	philo = create_philo(data, i, time);
	if (!philo)
		return (0);
	data->philo = philo;
	while (++i <= data->nb_philo)
	{
		philo->next = create_philo(data, i, time);
		if (!philo->next)
			return (0);
		philo = philo->next;
	}
	philo->next = data->philo;
	return (1);
}
