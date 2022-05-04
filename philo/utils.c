/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith <jsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 08:00:15 by jsmith            #+#    #+#             */
/*   Updated: 2022/05/03 11:59:53 by jsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	philo_thinks(t_philo *philo)
{
	if (philo->bill->corpse_404)
	{
		lock_print_unlock("is thinking", philo);
		return (false);
	}
	return (true);
}

bool	normative_check(t_philo *philo)
{
	if (!philo->bill->corpse_404)
	{
		pthread_mutex_unlock(philo->ffork_id);
		pthread_mutex_unlock(philo->sfork_id);
		return (true);
	}
	return (false);
}

int	ft_atoi(const char *str)
{
	long int	n;
	int			sign;

	n = 0;
	sign = 1;
	while ((*str <= 13 && *str >= 9) || *str == 32)
		str++;
	if (*str == '-')
		return (-1);
	else if (*str == '+')
		str++;
	while (*str)
	{
		if (*str >= '0' && *str <= '9')
			n = n * 10 + (*str++ - '0');
		else
			return (-1);
	}
	return ((int)(n * sign));
}

int	ft_isdigit(int c)
{
	if (c >= 48 && c <= 57)
		return (1);
	return (0);
}

bool	check_digit(char *argv[])
{
	int	i;
	int	u;

	u = 0;
	i = 1;
	while (argv[i])
	{
		u = 0;
		while (argv[i][u])
		{
			if (!ft_isdigit(argv[i][u]))
				return (true);
			u++;
		}
		i++;
	}
	return (false);
}
