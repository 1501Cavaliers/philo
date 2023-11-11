/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:16:39 by flavian           #+#    #+#             */
/*   Updated: 2023/11/11 18:55:49 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	int	gettime()
{
	struct timeval x;
	gettimeofday(&x, NULL);
	return ((long int)x.tv_sec * 1000 + (long int)x.tv_usec / 1000);
}

long	int	curenttime(long int start)
{
	return (gettime() - start);
}

int	my_sleep(t_philo *philo, long int tt_sleep)
{
	long int wake_up;

	if (check_death(philo))
		return (0);
	wake_up = curenttime(philo->start_time) + tt_sleep;
	while(wake_up > curenttime(philo->start_time))
	{
		usleep(1000);
		if (check_death(philo))
			return (0);
	}
	return (1);
}

int	say(t_philo *philo, char *g, int nb_fork)
{
	(void) nb_fork;
	// printf("SAY\n");
	if (check_death(philo))
		return (0);
	pthread_mutex_lock(&philo->data->write);
	printf("%ld philo %d %s\n", curenttime(philo->start_time), philo->name, g);
	pthread_mutex_unlock(&philo->data->write);
	return (1);
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
