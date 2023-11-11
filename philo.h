/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flavian <flavian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/30 12:10:38 by flavian           #+#    #+#             */
/*   Updated: 2023/11/11 18:50:13 by flavian          ###   ########.fr       */
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
	long	int		start_time;
	long	int		death_time;
	pthread_mutex_t	*r_fork;
	pthread_mutex_t	*l_fork;
	pthread_mutex_t	philock;
	struct s_data	*data;
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
	pthread_mutex_t	write;
	pthread_mutex_t	death;
	pthread_t		check;
}		t_data;

int			parsing(t_data *data, int ac, char **av);

int			ft_error(char *msg, int i);

int			init_mutex_data_pt1(t_data *data);

int			init_philo(t_data *data);

int			init_thread(t_data *data);

int			ft_strlen(char *str);

void		*dinner(void *arg);

int	say(t_philo *philo, char *g, int nb_fork);

long	int	gettime();

int			check_death(t_philo *philo);

int	my_sleep(t_philo *philo, long int tt_sleep);
long	int	curenttime(long int start);

void	*funeral(void *data);

int	ft_end(t_philo *philo, int forks);
int	locker(pthread_mutex_t *mutex, int check);
int	unlocker(pthread_mutex_t *mutex, int check);
int	check_other_died(t_philo *philo);



#endif