/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:41:15 by fserpe            #+#    #+#             */
/*   Updated: 2023/11/02 17:12:07 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	death_time(t_philo *philo)
{
	long	int	ttd;
	long	int	goal;
	long	int	actual;

	ttd = philo->data->tt_die;
	goal = ttd + (philo->ate * ttd);
	actual = gettime() - philo->start_time;
	if (actual >= goal)
	{
		philo->dying = 1;
		locker(&philo->data->death, 0);
		philo->data->is_dead = 1;
		unlocker(&philo->data->death, 0);

		say(philo, gettime() - philo->start_time, "is dead");
		return (0);
	}
	return (1);
}

int	thinking(t_philo *philo)
{
	if (philo->data->is_dead == 1)
		return (0);
	usleep(10);
	say(philo, gettime() - philo->start_time, "is thinking");
	return (1);
}

int	sleeping(t_philo *philo)
{
	long	int	time;

	if (philo->data->is_dead == 1)
		return (0);
	time = gettime() + philo->data->tt_sleep;
	while (gettime() < time)
		usleep(10);
	say(philo, gettime() - philo->start_time, "is sleeping");
	return (1);
}

int	eating(t_philo *philo)
{
	long	int	time;


	if (philo->data->is_dead == 1)
		return (0);
	time = gettime() + philo->data->tt_sleep;
	while (gettime() < time)
		usleep(10);
	philo->ate++;
	say(philo, gettime() - philo->start_time, "is eating");
	unlocker(philo->l_fork, philo->dying);
	unlocker(philo->r_fork, philo->dying);
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->data->nb_philo == 1)
	{
		say(philo, gettime() - philo->start_time, "has taken a fork");
		philo->dying = 1;
	}
	while (check_death(philo) == 1 && philo->ate != philo->data->nb_eat)
	{
		locker(philo->l_fork, philo->dying);
		say(philo, gettime() - philo->start_time, "has taken a fork");
		locker(philo->r_fork, philo->dying);
		say(philo, gettime() - philo->start_time, "has taken a fork");
		if (!eating(philo))
			break ;
		if (!sleeping(philo))
			break ;
		if (thinking(philo))
			break ;
	}
	return (NULL);
}

int	init_thread(t_data *data)
{
	int	i;
	t_philo	*philo;

	philo = data->philo;
	i = 0;
	while (philo && i < data->nb_philo)
	{
			if (pthread_create(&philo->id, NULL, &routine, philo) != 0)
				return (1);
		philo = philo->next;
		i++;
	}
	philo = data->philo;
	i = 0;
	while (philo && i < data->nb_philo)
	{
			if (pthread_join(philo->id, NULL) != 0)
				return (2);
		philo = philo->next;
		i++;
	}
	return (0);
}