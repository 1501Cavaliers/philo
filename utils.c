/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:16:39 by flavian           #+#    #+#             */
/*   Updated: 2023/11/09 20:25:51 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	int	curenttime(long int start)
{
	return (gettime() - start);
}

int		check_death(t_philo *philo, long int curent, long int death)
{
	pthread_mutex_lock(&philo->data->death);
	if (philo->data->is_dead == 1)
	{
		pthread_mutex_unlock(&philo->data->death);
		return (1);
	}
	
	if (death < curent)
	{
		printf("%ld philo %d died\n", curenttime(philo->start_time), philo->name);
		// pthread_mutex_unlock(&philo->data->write);
		// pthread_mutex_lock(&philo->data->death);
		philo->data->is_dead = 1;
		pthread_mutex_unlock(&philo->data->death);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->death);
	// pthread_mutex_unlock(&philo->data->death);
	return (0);
}

long int	my_sleep(long int death_time, t_philo *philo, long int u_sec)
{
	// pthread_mutex_lock(&philo->data->death);
	if (check_death(philo, curenttime(philo->start_time), death_time))
		return (-1);
	// while (u_sec)
	long int wake_up = curenttime(philo->start_time) + u_sec;
	while(wake_up > curenttime(philo->start_time))
	{
		// printf("i am %d\n", philo->name);
		usleep(1000);
		// pthread_mutex_lock(&philo->data->death);
		if (check_death(philo, curenttime(philo->start_time), death_time))
			return (-1);
		u_sec--;
	}
	return (death_time);
}

long int	say(t_philo *philo, long int death_time, char *g)
{
	// pthread_mutex_lock(&philo->data->death);
	if (check_death(philo, curenttime(philo->start_time), death_time))
		return (-1);
	pthread_mutex_lock(&philo->data->write);
	printf("%ld philo %d %s\n", curenttime(philo->start_time), philo->name, g);
	pthread_mutex_unlock(&philo->data->write);
	return (death_time);
}



int	ft_strlen(char *str)
{
	int	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}