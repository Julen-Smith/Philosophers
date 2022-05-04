/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_management.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith <jsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 11:44:16 by jsmith            #+#    #+#             */
/*   Updated: 2022/05/04 18:10:18 by jsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	refresh_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((long long)(t.tv_sec * 1000) + (long long)(t.tv_usec / 1000));
}

long long	time_diff(long long start, long long last)
{
	return (last - start);
}

void	own_usleep(long long m_usleep)
{
	long long	actual_time;

	actual_time = refresh_time();
	while (true)
	{
		if (!(time_diff(actual_time, refresh_time()) >= m_usleep))
			usleep(STD_WAIT);
		else
			return ;
	}
}

/*   ¯\_(ツ)_/¯   */
bool	must_die(t_philo *philo)
{
	if (philo->is_waiter)
	{
		own_usleep(philo->bill->life_long);
		printf("%lld %d died\n", philo->bill->life_long, CHECK_THREAD);
	}
	return (true);
}
