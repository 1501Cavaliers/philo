/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:41:15 by fserpe            #+#    #+#             */
/*   Updated: 2023/11/02 14:20:49 by flavian          ###   ########.fr       */
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
		philo->is_dead = 1;
		ft_end(philo);
		return (0);
	}
	return (1);
}

int	thinking(t_philo *philo)
{
	if (philo->is_dead && !check_death(philo))
		return (0);
	usleep(100);
	say(philo, gettime() - philo->start_time, "is thinking");
	return (1);
}

int	sleeping(t_philo *philo)
{
	if (philo->is_dead && !check_death(philo))
		return (0);
	usleep(philo->data->tt_sleep * 1e-3);
	say(philo, gettime() - philo->start_time, "is sleeping");
	return (1);
}

int	eating(t_philo *philo)
{
	if (philo->is_dead && !check_death(philo))
		return (0);
	usleep(philo->data->tt_eat * 1e-3);
	philo->ate++;
	say(philo, gettime() - philo->start_time, "is eating");
	unlocker(philo->l_fork, philo->is_dead);
	unlocker(philo->r_fork, philo->is_dead);
	return (1);
}

void	*routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *) arg;
	if (philo->data->nb_philo == 1)
	{
		say(philo, gettime() - philo->start_time, "has taken a fork");
		philo->is_dead = 1;
	}
	while (!philo->is_dead && check_death(philo) && philo->ate != philo->data->nb_eat)
	{
		locker(philo->l_fork, philo->is_dead);
		say(philo, gettime() - philo->start_time, "has taken a fork");
		locker(philo->r_fork, philo->is_dead);
		say(philo, gettime() - philo->start_time, "has taken a fork");
		eating(philo);
		if (philo->ate > 0)
			sleeping(philo);
		thinking(philo);
	}
	return (NULL);
}

int	init_thread(t_data *data)
{
	int	i;
	t_philo	*philo;

	philo = data->philo;
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_create(&philo->id, NULL, &routine, philo) != 0)
			return (1);
		philo = philo->next;
		i++;
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