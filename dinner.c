/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:41:15 by fserpe            #+#    #+#             */
/*   Updated: 2023/11/11 18:55:52 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	drop_a_fork(pthread_mutex_t *fork, pthread_mutex_t *status, int *v_status)
{
	(void) status;
	(void) v_status;

	// pthread_mutex_lock(status);
	// *v_status = 0;
	pthread_mutex_unlock(fork);
	// pthread_mutex_unlock(status);
}

void	catch_l_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->l_fork);
	say(philo, "has taken a fork", 1);
}

void	catch_r_fork(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	say(philo, "has taken a fork", 2);
}

void 	eating(t_philo *philo)
{
	// printf("--EAT--\n");
	say(philo, "is eating", 2);
	pthread_mutex_lock(&philo->philock);
	philo->ate++;
	philo->death_time += curenttime(philo->start_time); 
	pthread_mutex_unlock(&philo->philock);
	my_sleep(philo, philo->data->tt_eat);
	say(philo, "dropped forks", 2);
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}

void	sleeping(t_philo *philo)
{
	// printf("--SLEEP--\n");
	say(philo, "is sleeping", 0);
	my_sleep(philo, philo->data->tt_sleep);
}

void	*dinner(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->nb_philo == 1)
	{
		say(philo, "has taken a fork", -1);
		return (NULL);
	}
	pthread_mutex_lock(&philo->philock);
	while (philo->ate != philo->data->nb_eat && !check_death(philo))
	{
		pthread_mutex_unlock(&philo->philock);
		pthread_mutex_lock(philo->l_fork);
		say(philo, "has taken a fork", 1);
		// printf("DINNER\n");
		pthread_mutex_lock(philo->r_fork);
		say(philo, "has taken a fork", 2);
		eating(philo);
		sleeping(philo);
		say(philo, "is thinking", 0);
		pthread_mutex_lock(&philo->philock);	
	}
	if (philo->ate == philo->data->nb_eat)
	{
		pthread_mutex_lock(&philo->data->write);
		printf("%d has eaten %d times out of %ld\n", philo->name, philo->ate, philo->data->nb_eat);
		pthread_mutex_unlock(&philo->data->write);

	}
	pthread_mutex_unlock(&philo->philock);
	return (NULL);
}
