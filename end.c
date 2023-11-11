/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:51:11 by fserpe            #+#    #+#             */
/*   Updated: 2023/11/11 18:55:10 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// int	check_other_died(t_philo *philo)
// {
// 	pthread_mutex_lock(&philo->data->death);
// 	if (*philo->data->is_dead == 1)
// 	{
// 		pthread_mutex_unlock(&philo->data->death);
// 		return (1);
// 	}
// 	else if (!*philo->data->is_dead)
// 	{
// 		pthread_mutex_unlock(&philo->data->death);
// 		return (0);
// 	}
// 	return (0);
// }


int		check_death(t_philo *philo)
{
	int	dying;

	// printf("CHECK DEATH\n");
	pthread_mutex_lock(&philo->data->death);
	dying = *philo->is_dead;
	pthread_mutex_unlock(&philo->data->death);

		// printf("OUT CHECK DEATH\n");
	return (dying);
}

int	ft_end(t_philo *philo, int forks)
{
	// printf("in ft_end\n");
	if (forks == -1)
		return (0);
	pthread_mutex_lock(&philo->data->death);
	if (check_death(philo))
	{
		pthread_mutex_unlock(&philo->data->death);
		if (forks == 1 || forks == 2)
			pthread_mutex_unlock(philo->l_fork);
		if (forks == 2)
			pthread_mutex_unlock(philo->r_fork);
		*philo->is_dead = 1;
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death);
	return (0);
}

void	tumb(t_philo *philo, int philo_full)
{
	(void) philo_full;
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
		if ((philo->death_time < curenttime(philo->start_time) && (philo->ate != philo->data->nb_eat)) || (philo_full == philo->data->nb_philo))
			tumb(philo, philo_full);
		pthread_mutex_unlock(&philo->philock);
		philo = philo->next;
	}
		// printf("OUT FUNERAL\n");

	return (NULL);
}