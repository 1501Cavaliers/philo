/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:41:15 by fserpe            #+#    #+#             */
/*   Updated: 2023/11/01 12:37:15 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_death(t_philo *philo)
{
	long	int	goal;
	long	int	actual;

	goal = philo->data->tt_die;
	actual = gettime() - philo->start_time;
	if (actual >= goal)
	{
		philo->is_ended = 1;
		return (0);
	}
	return (1);
}

int	thinking(t_philo *philo)
{
	if (!check_death(philo))
		return (0);
	usleep(100);
	say(philo, gettime() - philo->start_time, "is thinking");
	return (1);
}

int	sleeping(t_philo *philo)
{
	if (!check_death(philo))
		return (0);
	usleep(philo->data->tt_sleep * 1e-3);
	say(philo, gettime() - philo->start_time, "is sleeping");
	return (1);
}

int	eating(t_philo *philo)
{
	if (!check_death(philo))
		return (0);
	usleep(philo->data->tt_eat * 1e-3);
	say(philo, gettime() - philo->start_time, "is eating");
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->data->nb_philo == 1)
	{
		say(philo, gettime() - philo->start_time, "has taken a fork");
		philo->is_ended = 1;
	}
	while (ft_end(philo) && philo->ate != philo->data->nb_eat)
	{
		say(philo, gettime() - philo->start_time, "has taken a fork");
		locker(philo->l_fork, philo->is_ended);
		say(philo, gettime() - philo->start_time, "has taken a fork");
		locker(philo->r_fork, philo->is_ended);
		eating(philo);
		unlocker(philo->l_fork, philo->is_ended);
		unlocker(philo->r_fork, philo->is_ended);
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