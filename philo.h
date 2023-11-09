/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:10:38 by flavian           #+#    #+#             */
/*   Updated: 2023/11/09 19:19:38 by flavian          ###   ########.fr       */
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
	int				dying;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	int				*status_left;
	int				*status_right;
	pthread_mutex_t	*r_status;
	pthread_mutex_t	*l_status;
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
	int				*v_status;
	pthread_mutex_t	*forks;
	pthread_mutex_t	write;
	pthread_mutex_t	death;
	pthread_mutex_t	*status;
}		t_data;

int			parsing(t_data *data, int ac, char **av);

int			ft_error(char *msg, int i);

int			init_mutex(t_data *data);

int			init_philo(t_data *data);

int			init_thread(t_data *data);

int			ft_strlen(char *str);

long int	say(t_philo *philo, long int death_time, char *msg);

long	int	gettime();

int			check_death(t_philo *philo, long int curent, long int death);

long int	my_sleep(long int death_time, t_philo *philo, long int u_sec);

long	int	curenttime(long int start);

int			ft_end(t_philo *philo);

#endif