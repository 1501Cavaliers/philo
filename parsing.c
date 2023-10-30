/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:24:12 by flavian           #+#    #+#             */
/*   Updated: 2023/10/30 15:55:05 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_atoi(char *nptr)
{
	int	i;
	int	sign;
	int	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while ((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' ')
		++i;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign *= -1;
		++i;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb *= 10;
		nb += nptr[i] - 48;
		++i;
	}
	return (sign * nb);
}

int	check_if_num(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ' || str[i] == '+' || str[i] == '-')
		++i;
	while (str[i])
	{
		if (str[i] < 48 || str[i] > 57)
			return (0);
		i++;
	}
	if (i > 0)
		return (1);
	else
		return (0);
}

int	parsing(t_data *data, char **av)
{
	int	tab[5];
	int	i;

	i = 1;
	while (av[i])
	{
		if (!check_if_num(av[i]))
			return (0);
		tab[i - 1] = ft_atoi(av[i]);
		i++;
	}
	if (i < 6)
		tab[4] = -1;
	data->nb_philo = tab[0];
	data->tt_die = tab[1];
	data->tt_eat = tab[2];
	data->tt_sleep = tab[3];
	data->nb_eat = tab[4];
	data->is_dead = 0;
	data->philo = NULL;
	// printf("nb of philo = %d\ntime to die = %d\ntime to eat = %d\ntime to sleep = %d\nnb of eat = %d\n", data->nb_philo, data->tt_die, data->tt_eat, data->tt_sleep, data->nb_eat);
	return (1);
}