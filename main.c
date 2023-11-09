/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:16:24 by flavian           #+#    #+#             */
/*   Updated: 2023/11/09 19:33:04 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_mutex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_mutex_destroy(&data->forks[i++]) != 0)
			return ;
		i++;
	}
	if (pthread_mutex_destroy(&data->write) != 0)
		return ;
	if (pthread_mutex_destroy(&data->death) != 0)
		return ;
}

void	free_philo(t_data *data)
{
	int	i;
	t_philo *philo;
	t_philo	*tmp;
	
	i = 1;
	philo = data->philo;
	if (data->nb_philo == 1)
		free(philo);
	else
	{
		while (i <= data->nb_philo)
		{
			tmp = philo->next;
			free(philo);
			philo = tmp;
			i++;
		}
	}
}

void	free_all(t_data *data)
{
	destroy_mutex(data);
	free(data->forks);
	free_philo(data);
	free(data->status);
	free(data->v_status);
	free(data);
}

int	ft_error(char *msg, int i)
{
	printf("%s\n", msg);
	return (i);
}

int	main(int ac, char **av)
{
	t_data	*data;

	if (ac < 5 || ac > 6)
		return (ft_error("Wrong number of arg", 0));
	data = NULL;
	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	if (!parsing(data, ac, av))
		return (ft_error("Parsing error", 1));
	if (init_mutex(data))
		return (ft_error("Mutex init error", 2));
	if (init_philo(data))
		return (ft_error("Philo init error", 3));
	if (init_thread(data))
		return (ft_error("Thread init error", 4));
	free_all(data);
	return (1);
}