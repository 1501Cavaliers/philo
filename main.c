/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:16:24 by flavian           #+#    #+#             */
/*   Updated: 2023/11/12 13:51:16 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_data *data, int val)
{
	int	i;
	int	err;

	i = 0;
	err = 0;
	if (val == 0)
		val = 4;
	if (val < 0)
		val = -val;
	if (err < val)
	{
		while (i < data->nb_philo && &data->forks[i])
		{
			if (pthread_mutex_destroy(&data->forks[i++]) != 0)
				return ;
			i++;
		}
		free(data->forks);
		err++;
	}
	destroy_mutex_2(data, val, err, 0);
}

void	free_philo(t_data *data)
{
	int		i;
	t_philo	*philo;
	t_philo	*tmp;

	i = 1;
	philo = data->philo;
	if (data->nb_philo == 1)
		free(philo);
	else
	{
		while (philo && i <= data->nb_philo)
		{
			tmp = philo->next;
			free(philo);
			philo = tmp;
			i++;
		}
	}
}

int	free_all(t_data *data, int val)
{
	destroy_mutex(data, val);
	if (data->philo != NULL)
		free_philo(data);
	free(data);
	return (0);
}

int	ft_error(char *msg, int i)
{
	printf("%s\n", msg);
	return (i);
}

int	main(int ac, char **av)
{
	t_data	*data;
	int		val;

	if (ac < 5 || ac > 6)
		return (ft_error("Wrong number of arg", 0));
	data = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	if (!parsing(data, ac, av))
	{
		free(data);
		return (ft_error("Parsing error", 1));
	}
	val = init_mutex_data_pt1(data);
	if (val != 0)
	{
		free_all(data, val);
		return (ft_error("Mutex init error", 2));
	}
	if (check_init_philo(data, val))
		return (ft_error("Philo init error", 3));
	if (create_thread(data))
		return (ft_error("Thread init error", 4));
	return (free_all(data, 0));
}
