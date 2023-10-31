/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:16:39 by flavian           #+#    #+#             */
/*   Updated: 2023/10/31 14:33:04 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	say(t_philo *philo, char *msg)
{
	struct timeval x;
	long	int time;

	gettimeofday(&x, NULL);
	time = 1e-3 * x.tv_usec;
	pthread_mutex_lock(&philo->data->write);
	printf("%ld %d %s\n", time, philo->name, msg);
	pthread_mutex_unlock(&philo->data->write);
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