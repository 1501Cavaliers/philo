/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   end.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 13:51:11 by fserpe            #+#    #+#             */
/*   Updated: 2023/10/31 13:57:46 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_end(t_philo *philo)
{
	if (philo->is_ended == 1)
	{
		philo->data->is_dead = 1;
		printf("Philo %d is dead\n", philo->name);
		// free_all;
		return (0);
	}
	return (1);
}