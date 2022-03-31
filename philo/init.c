/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:16:24 by yironmak          #+#    #+#             */
/*   Updated: 2022/03/31 23:16:08 by yironmak         ###   ########.fr       */
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

void	create_philos(int N, char **argv, t_philo **philos, t_mutex *forks)
{
	int	i;

	i = -1;
	gettimeofday(&((*philos)[0].tv_start), &((*philos)[0].tz));
	while (++i < N)
	{
		(*philos)[i].N = N;
		(*philos)[i].n = i;
		(*philos)[i].die_time = ft_atoi(argv[2]);
		(*philos)[i].eat_time = ft_atoi(argv[3]) * 1000;
		(*philos)[i].sleep_time = ft_atoi(argv[4]) * 1000;
		(*philos)[i].eat_n = 0;
		(*philos)[i].is_eat_n_spec = 1;
		if (argv[5])
			(*philos)[i].eat_max = ft_atoi(argv[5]);
		else
			(*philos)[i].is_eat_n_spec = 0;
		(*philos)[i].tv_start = (*philos)[0].tv_start;
		(*philos)[i].tz = (*philos)[0].tz;
		(*philos)[i].fork_r = &(forks[i]);
		(*philos)[i].fork_l = &(forks[get_fork(i - 1, N)]);
		pthread_create(&((*philos)[i].t), NULL, \
						create_philo, &(*philos)[i]);
		usleep(500);
	}
}
