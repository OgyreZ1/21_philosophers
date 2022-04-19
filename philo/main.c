/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:42:06 by yironmak          #+#    #+#             */
/*   Updated: 2022/04/19 12:39:44 by yironmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	die_check_philos(t_philo *philos, int N)
{
	int	i;

	i = -1;
	while (++i < N)
	{
		if (check_dying(philos + i))
			break ;
	}
}

int	get_status(t_philo *philo)
{
	int	res;

	res = 0;
	pthread_mutex_lock(philo->env->status_m);
	res = *(philo->env->status);
	pthread_mutex_unlock(philo->env->status_m);
	return (res);
}

int	free_all(t_philo *philos, t_mutex *forks, int N)
{
	int	i;

	if (philos->env->status)
		free(philos->env->status);
	if (philos->env->printable)
		free(philos->env->printable);
	if (philos->env->status_m)
		free(philos->env->status_m);
	if (philos->env)
		free(philos->env);
	if (philos)
	{
		i = -1;
		while (++i < N)
			free(philos[i].eat_n_mutex);
		free(philos);
	}
	if (forks)
		free(forks);
	return (0);
}

void	check_each_ate_n_times(t_philo *philos, t_mutex *forks, int N)
{
	int	i;

	i = -1;
	while (++i < N)
	{
		pthread_mutex_lock(philos[i].eat_n_mutex);
		if (philos[i].eat_n < philos[i].env->eat_min)
		{
			pthread_mutex_unlock(philos[i].eat_n_mutex);
			return ;
		}
		pthread_mutex_unlock(philos[i].eat_n_mutex);
	}
	pthread_mutex_lock(philos->env->printable);
	pthread_mutex_lock(philos->env->status_m);
	*(philos->env->status) = 1;
	pthread_mutex_unlock(philos->env->status_m);
	free_all(philos, forks, N);
	exit(0);
}

int	main(int argc, char **argv)
{
	t_philo			*philos;
	t_mutex			*forks;
	int				N;
	int				i;

	if (argc >= 5 && argc <= 6)
	{
		N = ft_atoi(argv[1]);
		philos = malloc(N * sizeof(t_philo));
		forks = malloc(N * sizeof(t_mutex));
		init_forks(N, forks);
		create_philos(N, argv, &philos, forks);
		i = -1;
		while (++i < N)
			pthread_join(philos[i].t, NULL);
		while (get_status(philos) == 0)
		{
			if (philos[0].env->is_eat_n_spec)
				check_each_ate_n_times(philos, forks, N);
			die_check_philos(philos, N);
		}
		return (free_all(philos, forks, N));
	}
	else
		printf("Invalid number of arguments\n");
}
