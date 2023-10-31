/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:10:38 by flavian           #+#    #+#             */
/*   Updated: 2023/10/31 14:50:25 by fserpe           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdint.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <time.h>
# include <sys/time.h>

struct	s_data;

typedef struct s_philo
{
	struct s_data	*data;
	pthread_t		id;
	int				name;
	long	int		start_time;
	int				ate;
	int				is_ended;
	int				status;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	philock;
	struct s_philo	*next;
}		t_philo;

typedef struct s_data
{
	struct s_philo	*philo;
	long	int		nb_philo;
	long	int		tt_die;
	long	int		tt_eat;
	long	int		tt_sleep;
	long	int		nb_eat;
	int				is_dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*philock;
	pthread_mutex_t	death;
	pthread_mutex_t	write;
}		t_data;

int		parsing(t_data *data, char **av);

int		ft_error(char *msg, int i);

int		init_mutex(t_data *data);

int	init_philo(t_data *data);

int		init_thread(t_data *data);

int		ft_strlen(char *str);

int	ft_strncmp(char *s1, char *s2, int len);

void	say(t_philo *philo, char *msg);


int	ft_end(t_philo *philo);

#endif