/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 11:41:15 by fserpe            #+#    #+#             */
/*   Updated: 2023/11/09 20:28:54 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	drop_a_fork(pthread_mutex_t *fork, pthread_mutex_t *status, int *v_status)
{
	(void) status;
	(void) v_status;

	// pthread_mutex_lock(status);
	*v_status = 0;
	pthread_mutex_unlock(fork);
	// pthread_mutex_unlock(status);
}

int	catch_a_fork(t_philo *philo, long int death_time)
{
	// pthread_mutex_lock(philo->l_status);
	// int i = 0;
	// while (*philo->status_left == 1)
	// {
	// 	// if (i++ % 100 == 0)
	// 	// 	printf("%d is blocked \n", philo->name);
	// 	pthread_mutex_unlock(philo->l_status);
	// 	usleep(100);
	// 	pthread_mutex_lock(philo->l_status);
	// }
	pthread_mutex_lock(philo->l_fork);
	// *philo->status_left = 1;
	// pthread_mutex_unlock(philo->l_status);
	
	if (say(philo, death_time, "has taken a fork") < 0)
	{
		drop_a_fork(philo->l_fork, philo->l_status, philo->status_left);
		return (0);
	}
	// pthread_mutex_lock(philo->r_status);
	// while (*philo->status_right == 1)
	// {
	// 	pthread_mutex_unlock(philo->r_status);
	// 	usleep(1);
	// 	pthread_mutex_lock(philo->r_status);
	// }
	// pthread_mutex_lock(philo->r_fork);
	// *philo->status_right = 1;
	// pthread_mutex_unlock(philo->r_status);
	if (say(philo, death_time, "has taken a fork") < 0)
	{
		drop_a_fork(philo->l_fork, philo->l_status, philo->status_left);
		drop_a_fork(philo->r_fork, philo->r_status, philo->status_right);
		return (0);
	}
	return (1);
}

long int	eating(t_philo *philo, long int death_time)
{
	
	if (check_death(philo, curenttime(philo->start_time), death_time))
		return (-1);
	if (death_time > 0)
	{
		death_time = say(philo, death_time, "is eating");
		philo->ate++;
		death_time = curenttime(philo->start_time) + philo->data->tt_die;
		death_time = my_sleep(death_time, philo, philo->data->tt_eat);
		// death_time = curenttime(philo->start_time) + philo->data->tt_die;
		say(philo, death_time, "dropped forks");
		drop_a_fork(philo->l_fork, philo->l_status, philo->status_left);
		drop_a_fork(philo->r_fork, philo->r_status, philo->status_right);
		return (death_time);
	}
	else
		return (-1);
}

long int	sleeping(t_philo *philo, long int death_time)
{
	if (check_death(philo, curenttime(philo->start_time), death_time))
		return (-1);
	if (death_time > 0)
	{
		death_time = say(philo, death_time, "is sleeping");
		death_time = my_sleep(death_time, philo, philo->data->tt_sleep);
		return (death_time);
	}
	else
		return (-1);
}

long int	thinking(t_philo *philo, long int death_time)
{
	if (check_death(philo, curenttime(philo->start_time), death_time))
		return (-1);
	if (death_time > 0)
	{
		death_time = say(philo, death_time, "is thinking");
		return (death_time);
	}
	else
		return (-1);
}

void	*dinner(void *arg)
{
	t_philo	*philo;
	long	int	death_time;

	philo = (t_philo *)arg;
	death_time = philo->data->tt_die;
	if (philo->data->nb_philo % 2 == 0 && philo->name % 2 == 0)
		usleep(1000);
	if (philo->data->nb_philo % 2  == 1 && philo->name % 2 == 1)
		usleep(1000);
	if (philo->data->nb_philo == 1)
	{
		say(philo, death_time, "has taken a fork");
		say(philo, death_time, "died");
		philo->data->is_dead = 1;
	}
	while (philo->ate != philo->data->nb_eat && philo->data->is_dead == 0 && death_time > 0)
	{
		
		if (!catch_a_fork(philo, death_time))
			break;
		if (philo->data->is_dead == 0)
			death_time = eating(philo, death_time);
		if (philo->data->is_dead == 0)
			death_time = sleeping(philo, death_time);
		if (philo->data->is_dead == 0)
			death_time = thinking(philo, death_time);
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
			if (pthread_create(&philo->id, NULL, &dinner, philo) != 0)
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