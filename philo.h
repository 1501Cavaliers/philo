/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fserpe <fserpe@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:10:38 by flavian           #+#    #+#             */
/*   Updated: 2023/11/12 13:51:47 by fserpe           ###   ########.fr       */
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
	pthread_t		id;
	int				name;
	int				ate;
	int				*is_dead;
	long int		start_time;
	long int		death_time;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	philock;
	struct s_data	*data;
	struct s_philo	*next;
}		t_philo;

typedef struct s_data
{
	struct s_philo	*philo;
	long int		nb_philo;
	long int		tt_die;
	long int		tt_eat;
	long int		tt_sleep;
	long int		nb_eat;
	int				is_dead;
	pthread_mutex_t	*forks;
	pthread_mutex_t	*philock;
	pthread_mutex_t	write;
	pthread_mutex_t	death;
	pthread_t		check;
}		t_data;

int			ft_error(char *msg, int i);

int			ft_strlen(char *str);

int			free_all(t_data *data, int val);

int			parsing(t_data *data, int ac, char **av);

int			init_mutex_data_pt1(t_data *data);

void		destroy_mutex_2(t_data *data, int val, int err, int i);

int			init_philo(t_data *data);

int			check_init_philo(t_data *data, int val);

int			create_thread(t_data *data);

void		*dinner(void *arg);

int			say(t_philo *philo, char *g);

int			my_sleep(t_philo *philo, long int tt_sleep);

long int	gettime(void);

long int	curenttime(long int start);

int			check_death(t_philo *philo);

void		*funeral(void *data);

#endif