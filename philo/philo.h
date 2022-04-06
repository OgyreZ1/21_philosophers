/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 13:12:01 by yironmak          #+#    #+#             */
/*   Updated: 2022/04/06 18:16:04 by yironmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <unistd.h>
typedef pthread_mutex_t	t_mutex;

typedef struct s_philo
{
	pthread_t		t;
	struct timezone	tz;
	struct timeval	tv_start;
	int				last_eat;
	t_mutex			*fork_l;
	t_mutex			*fork_r;
	int				n;
	int				N;
	int				die_time;
	int				eat_time;
	int				sl_time;
	int				is_eat_n_spec;
	int				eat_n;
	int				eat_min;
	int				works;
}	t_philo;

int		ft_atoi(const char *str);
int		get_ts(t_philo *philo);
void	init_forks(int N, t_mutex *forks);
void	create_philos(int N, char **argv, t_philo **philos, t_mutex *forks);
void	*create_philo(void *philo);

#endif