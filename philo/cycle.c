/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 13:10:16 by yironmak          #+#    #+#             */
/*   Updated: 2022/04/19 12:43:18 by yironmak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	msg(t_philo *philo, int ts, char *str)
{
	pthread_mutex_lock(philo->env->printable);
	printf("%d %d %s\n", ts, philo->n + 1, str);
	pthread_mutex_unlock(philo->env->printable);
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
	if (last_eat_long > philo->env->die_time + 5)
	{
		pthread_mutex_lock(philo->env->printable);
		printf("%d %d %s\n", get_ts(philo), philo->n + 1, DIE);
		pthread_mutex_lock(philo->env->status_m);
		*(philo->env->status) = 1;
		pthread_mutex_unlock(philo->env->status_m);
		return (1);
	}
	return (0);
}

void	eat(t_philo *philo)
{
	msg(philo, get_ts(philo), FORK);
	msg(philo, get_ts(philo), EAT);
	pthread_mutex_lock(philo->eat_n_mutex);
	philo->eat_n += 1;
	pthread_mutex_unlock(philo->eat_n_mutex);
}

void	philo_cycle(t_philo *philo)
{
	int	tmp;
	int	i;

	i = -1;
	while (++i < philo->env->eat_min || ! philo->env->is_eat_n_spec)
	{
		msg(philo, get_ts(philo), THINK);
		if (pthread_mutex_lock(philo->fork_l) == 0)
		{
			check_dying(philo);
			msg(philo, get_ts(philo), FORK);
			pthread_mutex_lock(philo->fork_r);
			eat(philo);
			tmp = get_ts(philo);
			while (get_ts(philo) < tmp + philo->env->eat_time / 1000)
				usleep(1000);
			philo->last_eat = get_ts(philo);
			msg(philo, tmp + philo->env->eat_time / 1000, SLEEP);
			pthread_mutex_unlock(philo->fork_l);
			pthread_mutex_unlock(philo->fork_r);
			while (get_ts(philo) < philo->last_eat + philo->env->sl_time / 1000)
				usleep(1000);
		}
	}
}
