/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith <jsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/11 11:47:23 by jsmith            #+#    #+#             */
/*   Updated: 2022/05/03 11:58:46 by jsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	infiltrated_check(t_philo *philo)
{
	int	i;
	int	timestamp;

	philo->bill->finished = 0;
	while (true)
	{	
		i = 0;
		while (i != philo->bill->philonbr)
		{
			timestamp = refresh_time() - philo->bill->clients[i].last_lunch;
			if (timestamp > philo->bill->life_long && philo[i].last_lunch != 0)
			{
				philo->bill->corpse_404 = false;
				pthread_mutex_lock(&philo->write_permission);
				printf("%lld %d %s\n", time_diff(philo->bill->first_timestamp, \
				refresh_time()), philo->bill->clients[i].philo_id + AVOID,
					"died");
				pthread_mutex_unlock(&philo->write_permission);
				return (true);
			}
			if (philo->bill->finished == philo->bill->philonbr - 1)
				return (true);
			i++;
		}
	}
}

void	*exec(void *uknown)
{
	t_philo	*philo;

	philo = (t_philo *)uknown;
	if (philo->bill->philonbr == 1 && must_die(philo))
		return (NULL);
	philo->last_lunch = refresh_time();
	philo->bill->first_timestamp = refresh_time();
	while (philo->bill->corpse_404)
	{
		if (philo->is_waiter && infiltrated_check(philo))
			return (NULL);
		if (philo_forks(philo))
			return (NULL);
		if (philo_eats(philo))
			return (NULL);
		if (philo_sleeps(philo))
			return (NULL);
		if (philo_thinks(philo))
			return (NULL);
	}
	return (NULL);
}

void	free_stuff(t_bill *bill)
{
	int	i;

	i = 0;
	while (i != bill->philonbr)
	{
		pthread_mutex_destroy(&bill->cuttlery[i]);
		pthread_mutex_destroy(&bill->clients[i].write_permission);
		i++;
	}
	free(bill->pids);
	free(bill->cuttlery);
	free(bill->clients);
}

void	philosophers(int argc, char *argv[])
{
	t_bill	bill;

	init_bill(argc, argv, &bill);
	init_mutex(&bill);
	init_clients(&bill);
	init_threads(&bill);
	free_stuff(&bill);
}

int	main(int argc, char *argv[])
{	
	if (argc < 5 || argc > 6 || check_digit(argv))
		printf("Arg error\n");
	else
		philosophers(argc, argv);
	return (0);
}
