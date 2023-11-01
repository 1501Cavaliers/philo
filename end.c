/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:51:11 by fserpe            #+#    #+#             */
/*   Updated: 2023/11/01 12:32:38 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_end(t_philo *philo)
{
	if (philo->is_ended == 1)
	{
		philo->data->is_dead = 1;
		say(philo, gettime() - philo->start_time, "is dead");
		return (0);
	}
	else
		return (1);
}