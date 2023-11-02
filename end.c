/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:51:11 by fserpe            #+#    #+#             */
/*   Updated: 2023/11/02 12:07:25 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_end(t_philo *philo)
{
	if (philo->is_ended == 1)
	{
		locker(&philo->data->death, philo->is_ended);
		philo->data->is_dead = 1;
		unlocker(&philo->data->death, philo->is_ended);
		locker(&philo->data->write, philo->is_ended);
		say(philo, gettime() - philo->start_time, "is dead");
		unlocker(&philo->data->write, philo->is_ended);
		return (0);
	}
	else
		return (1);
}