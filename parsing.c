/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:24:12 by flavian           #+#    #+#             */
/*   Updated: 2023/11/12 10:49:16 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	int	ft_long_atoi(char *nptr)
{
	int			i;
	long int	sign;
	long int	nb;

	i = 0;
	sign = 1;
	nb = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb *= 10;
		nb += nptr[i] - 48;
		++i;
	}
	return (sign * nb);
}

int	ft_check_int(int ac, char **av)
{
	unsigned long long	tmp;

	if (ac == 6)
	{
		if (ft_strlen(av[5]) > 10)
			return (0);
		tmp = ft_long_atoi(av[5]);
		if (tmp > __INT_MAX__)
			return (0);
		ac--;
	}
	if (ft_strlen(av[1]) > 10)
		return (0);
	tmp = ft_long_atoi(av[1]);
	if (tmp > __INT_MAX__)
		return (0);
	ac--;
	while (ac > 1)
	{
		if (ft_strlen(av[ac]) > 9)
			return (0);
		ac--;
	}
	return (1);
}

int	check_if_num(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
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

int	init_data(t_data *data, int tab[5])
{
	data->nb_philo = tab[0];
	if (data->nb_philo <= 0)
		return (0);
	data->tt_die = tab[1];
	if (data->tt_die == 0)
		return (0);
	data->tt_eat = tab[2];
	if (data->tt_eat == 0)
		return (0);
	data->tt_sleep = tab[3];
	if (data->tt_sleep == 0)
		return (0);
	data->nb_eat = tab[4];
	data->is_dead = 0;
	data->philo = NULL;
	return (1);
}

int	parsing(t_data *data, int ac, char **av)
{
	int	tab[5];
	int	i;

	i = 1;
	if (!ft_check_int(ac, av))
	{
		printf("error int overflow\n");
		return (0);
	}
	while (av[i])
	{
		if (!check_if_num(av[i]))
			return (0);
		tab[i - 1] = ft_long_atoi(av[i]);
		i++;
	}
	if (i < 6)
		tab[4] = -1;
	if (!init_data(data, tab))
		return (0);
	return (1);
}
