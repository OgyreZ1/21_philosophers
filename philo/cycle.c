/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cycle.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yironmak <yironmak@student.21-school.ru    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 13:10:16 by yironmak          #+#    #+#             */
/*   Updated: 2022/04/06 18:21:27 by yironmak         ###   ########.fr       */
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

void	check_dying(t_philo *philo)
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
		usleep(1000);
		printf("%d %d died\n", get_ts(philo), philo->n + 1);
		philo->works = 0;
	}
}

void	msg(t_philo *philo, int ts, int msg_n)
{
	if (msg_n == 0)
		printf("%d %d has taken a fork\n", ts, philo->n + 1);
	else if (msg_n == 1)
		printf("%d %d is eating\n", ts, philo->n + 1);
	else if (msg_n == 2)
		printf("%d %d is sleeping\n", ts, philo->n + 1);
	else if (msg_n == 3)
		printf("%d %d is thinking\n", ts, philo->n + 1);
}

void	philo_cycle(t_philo *philo)
{
	int	tmp;

	while (philo->works)
	{
		if (pthread_mutex_lock(philo->fork_l) == 0)
		{
			check_dying(philo);
			msg(philo, get_ts(philo), 0);
			pthread_mutex_lock(philo->fork_r);
			tmp = get_ts(philo);
			msg(philo, tmp, 0);
			msg(philo, tmp, 1);
			if (philo->is_eat_n_spec)
				philo->eat_n++;
			while (get_ts(philo) < tmp + philo->eat_time / 1000)
				usleep(1000);
			philo->last_eat = get_ts(philo);
			msg(philo, tmp + philo->eat_time / 1000, 2);
			pthread_mutex_unlock(philo->fork_l);
			pthread_mutex_unlock(philo->fork_r);
			while (get_ts(philo) < philo->last_eat + philo->sl_time / 1000)
				usleep(1000);
			msg(philo, tmp + (philo->eat_time + philo->sl_time) / 1000, 3);
		}
	}
}

void	*create_philo(void *philo)
{
	pthread_detach(((t_philo *)philo)->t);
	philo_cycle(((t_philo *)philo));
	return (NULL);
}
