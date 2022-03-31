/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 13:10:16 by yironmak          #+#    #+#             */
/*   Updated: 2022/03/31 23:54:50 by yironmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_ts(t_philo *philo)
{
	struct timeval	tmp;

	gettimeofday(&tmp, &(philo->tz));
	return ((tmp.tv_sec - philo->tv_start.tv_sec) * 1000 + \
	(tmp.tv_usec - philo->tv_start.tv_usec) / 1000);
}

int	check_dying(t_philo *philo)
{
	long int		now;
	int				last_eat_long;
	struct timeval	tmp;

	gettimeofday(&tmp, &(philo->tz));
	now = (tmp.tv_sec - philo->tv_start.tv_sec) * 1000 + \
	(tmp.tv_usec - philo->tv_start.tv_usec) / 1000;
	last_eat_long = now - philo->last_eat;
	if (last_eat_long > philo->die_time)
	{
		printf("%d last eat %d %d\n", philo->n + 1, now, philo->last_eat);
		return (1);
	}
	return (0);
}

int	philo_cycle(t_philo *philo)
{
	int	tmp;

	while (1)
	{
		if (pthread_mutex_lock(philo->fork_l) == 0)
		{
			if (check_dying(philo))
			{
				printf("%ld %d died\n", get_ts(philo), philo->n + 1);
				exit(0);
			}
			printf("%d %d has taken a fork\n", get_ts(philo), philo->n + 1);
			pthread_mutex_lock(philo->fork_r);
			tmp = get_ts(philo);
			printf("%d %d has taken a fork\n", tmp, philo->n + 1);
			printf("%d %d is eating\n", tmp, philo->n + 1);
			while (get_ts(philo) < tmp + philo->eat_time / 1000)
				usleep(1000);
			philo->last_eat = get_ts(philo);
			printf("%d %d is sleeping\n", tmp + philo->eat_time / 1000, philo->n + 1);
			pthread_mutex_unlock(philo->fork_l);
			pthread_mutex_unlock(philo->fork_r);
			while (get_ts(philo) < philo->last_eat + philo->sleep_time / 1000)
				usleep(1000);
			printf("%d %d is thinking\n", tmp + (philo->eat_time + philo->sleep_time) / 1000, philo->n + 1);
		}
	}
}

void	*create_philo(void *philo)
{
	philo_cycle(((t_philo *)philo));
	return (NULL);
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
	}
	else
		printf("Invalid number of arguments\n");
}
