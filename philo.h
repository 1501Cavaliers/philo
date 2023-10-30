/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:10:38 by flavian           #+#    #+#             */
/*   Updated: 2023/10/30 15:55:44 by flavian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

struct	s_data;

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		id;
	int				name;
	int				start_time;
	int				is_ended;
	int				is_eating;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	philock;
	struct s_philo	*next;
}		t_philo;

typedef struct s_data
{
	struct s_philo	*philo;
	int				nb_philo;
	int				tt_die;
	int				tt_eat;
	int				tt_sleep;
	int				nb_eat;
	int				is_dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*philock;
	pthread_mutex_t	death;
	pthread_mutex_t	write;
}		t_data;

int	parsing(t_data *data, char **av);

int	ft_error(char *msg, int i);

int	init_mutex(t_data *data);

int	init_philo(t_data *data);

#endif