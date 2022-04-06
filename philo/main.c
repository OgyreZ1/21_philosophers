/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 17:42:06 by yironmak          #+#    #+#             */
/*   Updated: 2022/04/06 18:21:02 by yironmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_each_ate_n_times(t_philo *philos, int N, t_mutex *forks)
{
	int	f;
	int	i;

	i = -1;
	f = 0;
	while (++i < N)
		if (philos[i].eat_n >= philos[i].eat_min)
			f++;
	if (f == N)
	{
		i = -1;
		while (++i < N)
			pthread_mutex_destroy(&(forks[i]));
		free(philos);
		free(forks);
		exit(0);
	}
}

void	check_working_status(t_philo *philos, int N, t_mutex *forks)
{
	int	i;
	int	f;

	i = -1;
	f = 0;
	while (++i < N)
	{
		if (philos[i].works == 0)
		{
			f = 1;
			break ;
		}
	}
	i = -1;
	if (f)
	{
		while (++i < N)
		{
			philos[i].works = 0;
			pthread_mutex_destroy(&(forks[i]));
		}
	}
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
		while (1)
		{
			check_working_status(philos, N, forks);
			if (philos[0].is_eat_n_spec)
				check_each_ate_n_times(philos, N, forks);
		}
		i = -1;
		while (++i < N)
			pthread_join(philos[i].t, NULL);
	}
	else
		printf("Invalid number of arguments\n");
}
