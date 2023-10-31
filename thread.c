/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:41:15 by fserpe            #+#    #+#             */
/*   Updated: 2023/10/31 14:48:09 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thinking(t_philo *philo)
{
	philo->status = 3;
	say(philo, "is thinking");
}

void	sleeping(t_philo *philo)
{
	philo->status = 2;
	usleep(philo->data->tt_sleep * 1e-3);
	say(philo, "is sleeping");
}

void	eating(t_philo *philo)
{
	philo->status = 1;
	usleep(philo->data->tt_eat * 1e-3);
	say(philo, "is eating");
	philo->ate++;
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->data->nb_philo == 1)
	{
		say(philo, "Has taken a fork");
		philo->is_ended = 1;
	}
	while (ft_end(philo) && philo->data->nb_eat > 0 && philo->ate < philo->data->nb_eat)
	{
		say(philo, "Has taken a fork");
		pthread_mutex_lock(philo->l_fork);
		say(philo, "Has taken a fork");
		pthread_mutex_lock(philo->r_fork);
		eating(philo);
		pthread_mutex_unlock(philo->l_fork);
		pthread_mutex_unlock(philo->r_fork);
		sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

int	init_thread(t_data *data)
{
	t_philo	*philo;

	philo = data->philo;
	while (philo->next)
	{
		if (pthread_create(&philo->id, NULL, &routine, philo) != 0)
			return (1);
		philo = philo->next;
	}
	philo = data->philo;
	while (philo->next)
	{
		if (pthread_join(philo->id, NULL) != 0)
			return (2);
		philo = philo->next;
	}
	return (0);
}