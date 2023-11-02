/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:16:39 by flavian           #+#    #+#             */
/*   Updated: 2023/11/02 17:09:40 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int		check_death(t_philo *philo)
{
	// printf("ICI\n");
	if (!death_time(philo))
		return (0);
	if (philo->dying == 1)
	{
		say(philo, gettime() - philo->start_time, "is dead");
		pthread_mutex_lock(&philo->data->death);
		philo->data->is_dead = 1;
		pthread_mutex_unlock(&philo->data->death);
		return (0);
	}
	return (1);
}

void	say(t_philo *philo, long int time, char *msg)
{
	pthread_mutex_lock(&philo->data->write);
	printf("%ld %d %s\n", time, philo->name, msg);
	pthread_mutex_unlock(&philo->data->write);
}

int	locker(pthread_mutex_t *mutex, int check)
{
	if (check == 1)
		return (0);
	pthread_mutex_lock(mutex);
	return (1);
}

int	unlocker(pthread_mutex_t *mutex, int check)
{
	if (check == 1)
		return (0);
	pthread_mutex_unlock(mutex);
	return (1);
}

int	ft_strncmp(char *s1, char *s2, int len)
{
	int i;

	if (!s1 || !s2 || len <= 0)
		return (1);
	i = 0;
	while (s1[i] && s2[i] && i < len)
	{
		if (s1[i] != s2[i])
			return (2);
		i++;
	}
	return (s1[i] - s2[i]);
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