/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_does.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith <jsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/21 20:28:12 by jsmith            #+#    #+#             */
/*   Updated: 2022/05/04 18:07:57 by jsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	lock_print_unlock(char *philo_action, t_philo *philo)
{
	if (philo->bill->corpse_404)
	{
		pthread_mutex_lock(&philo->write_permission);
		printf("%lld %d %s\n", time_diff(philo->bill->first_timestamp,
				refresh_time()), philo->philo_id + AVOID, philo_action);
		pthread_mutex_unlock(&philo->write_permission);
	}
}

bool	philo_forks_impar(t_philo *philo)
{	
	if (!philo->ready)
	{
		own_usleep(STD_WAIT);
		philo->ready = true;
	}
	if (philo->bill->corpse_404)
	{
		pthread_mutex_lock(philo->ffork_id);
		pthread_mutex_lock(philo->sfork_id);
		if (!philo->bill->corpse_404)
		{	
			pthread_mutex_unlock(philo->ffork_id);
			pthread_mutex_unlock(philo->sfork_id);
			return (true);
		}
		lock_print_unlock("has taken a fork", philo);
		lock_print_unlock("has taken a fork", philo);
		pthread_mutex_unlock(philo->ffork_id);
		pthread_mutex_unlock(philo->sfork_id);
		return (false);
	}
	return (true);
}

bool	philo_forks(t_philo *philo)
{
	if (philo->bill->corpse_404)
	{
		if (philo->philo_id % 2 == 0
			&& philo->philo_id + 1 != philo->bill->philonbr)
		{
			pthread_mutex_lock(philo->ffork_id);
			pthread_mutex_lock(philo->sfork_id);
			if (normative_check(philo))
				return (true);
			lock_print_unlock("has taken a fork", philo);
			lock_print_unlock("has taken a fork", philo);
			pthread_mutex_unlock(philo->ffork_id);
			pthread_mutex_unlock(philo->sfork_id);
			return (false);
		}
		else
		{
			if (philo_forks_impar(philo))
				return (true);
			return (false);
		}	
	}
	return (true);
}

bool	philo_eats(t_philo *philo)
{	
	if (philo->bill->corpse_404)
	{	
		pthread_mutex_lock(philo->ffork_id);
		pthread_mutex_lock(philo->sfork_id);
		philo->last_lunch = refresh_time();
		lock_print_unlock("is eating", philo);
		if (philo->bill->flag)
		{
			philo->nbr_lunch++;
			if (philo->nbr_lunch >= philo->bill->max_eat)
			{	
				philo->bill->finished += 1;
				pthread_mutex_unlock(philo->ffork_id);
				pthread_mutex_unlock(philo->sfork_id);
				return (true);
			}
		}	
		own_usleep(philo->bill->eat_long);
		pthread_mutex_unlock(philo->ffork_id);
		pthread_mutex_unlock(philo->sfork_id);
		return (false);
	}
	return (true);
}

bool	philo_sleeps(t_philo *philo)
{	
	if (philo->bill->corpse_404)
	{
		lock_print_unlock("is sleeping", philo);
		own_usleep(philo->bill->sleep_long);
		return (false);
	}
	return (true);
}
