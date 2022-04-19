/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:16:24 by yironmak          #+#    #+#             */
/*   Updated: 2022/04/19 12:36:04 by yironmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_fork(int n, int N)
{
	if (n == -1)
		return (N - 1);
	return (n);
}

void	init_forks(int N, t_mutex *forks)
{
	int	i;

	i = -1;
	while (++i < N)
		pthread_mutex_init(&(forks[i]), NULL);
}

t_env	*init_env(int N, char **argv)
{
	t_env	*env;

	env = malloc(sizeof(t_env));
	env->N = N;
	env->die_time = ft_atoi(argv[2]);
	env->eat_time = ft_atoi(argv[3]) * 1000;
	env->sl_time = ft_atoi(argv[4]) * 1000;
	env->status_m = malloc(sizeof(t_mutex));
	env->status = malloc(sizeof(int));
	env->printable = malloc(sizeof(t_mutex));
	pthread_mutex_init(env->printable, NULL);
	pthread_mutex_init(env->status_m, NULL);
	*(env->status) = 0;
	env->is_eat_n_spec = 1;
	if (argv[5])
		env->eat_min = ft_atoi(argv[5]);
	else
		env->is_eat_n_spec = 0;
	return (env);
}

void	create_philos(int N, char **argv, t_philo **philos, t_mutex *forks)
{
	int		i;
	t_env	*env;

	i = -1;
	gettimeofday(&((*philos)[0].tv_start), &((*philos)[0].tz));
	env = init_env(N, argv);
	while (++i < N)
	{
		(*philos)[i].env = env;
		(*philos)[i].n = i;
		(*philos)[i].eat_n = 0;
		(*philos)[i].eat_n_mutex = malloc(sizeof(t_mutex));
		pthread_mutex_init((*philos)[i].eat_n_mutex, NULL);
		(*philos)[i].last_eat = 0;
		(*philos)[i].tv_start = (*philos)[0].tv_start;
		(*philos)[i].tz = (*philos)[0].tz;
		(*philos)[i].fork_r = &(forks[i]);
		(*philos)[i].fork_l = &(forks[get_fork(i - 1, N)]);
		pthread_create(&((*philos)[i].t), NULL, \
						create_philo, &(*philos)[i]);
		usleep(500);
	}
	i = -1;
	while (++i < N)
		pthread_detach((*philos)[i].t);
}

void	*create_philo(void *philo)
{
	philo_cycle(((t_philo *)philo));
	return (NULL);
}
