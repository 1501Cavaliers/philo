/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:41:15 by fserpe            #+#    #+#             */
/*   Updated: 2023/11/12 13:36:42 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_philo *philo)
{
	say(philo, "is eating");
	pthread_mutex_lock(&philo->philock);
	philo->ate++;
	philo->death_time += curenttime(philo->start_time);
	pthread_mutex_unlock(&philo->philock);
	my_sleep(philo, philo->data->tt_eat);
	say(philo, "dropped forks");
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	sleeping(t_philo *philo)
{
	say(philo, "is sleeping");
	my_sleep(philo, philo->data->tt_sleep);
}

void	*dinner(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nb_philo == 1)
	{
		say(philo, "has taken a fork");
		return (NULL);
	}
	pthread_mutex_lock(&philo->philock);
	while (philo->ate != philo->data->nb_eat && !check_death(philo))
	{
		pthread_mutex_unlock(&philo->philock);
		pthread_mutex_lock(philo->l_fork);
		say(philo, "has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		say(philo, "has taken a fork");
		eating(philo);
		sleeping(philo);
		say(philo, "is thinking");
		pthread_mutex_lock(&philo->philock);
	}
	pthread_mutex_unlock(&philo->philock);
	return (NULL);
}
