/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_manager.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith <jsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 18:11:08 by jsmith            #+#    #+#             */
/*   Updated: 2022/04/30 23:14:57 by jsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_bill(int argc, char *argv[], t_bill *bill)
{
	bill->philonbr = ft_atoi(argv[1]);
	bill->life_long = ft_atoi(argv[2]);
	bill->eat_long = ft_atoi(argv[3]);
	bill->sleep_long = ft_atoi(argv[4]);
	if (argc == 6)
	{
		bill->flag = true;
		bill->max_eat = ft_atoi(argv[5]);
	}
	else
	{
		bill->max_eat = -1;
		bill->flag = false;
	}
	bill->finished = 0;
	bill->corpse_404 = true;
}

void	init_clients(t_bill *bill)
{
	int			i;
	t_philo		*philo;

	i = 0;
	philo = (t_philo *) malloc(sizeof(t_philo)
			* (bill->philonbr + CHECK_THREAD));
	while (i != bill->philonbr)
	{
		philo[i].philo_id = i;
		philo[i].last_lunch = refresh_time();
		philo[i].is_waiter = false;
		philo[i].ffork_id = &bill->cuttlery[philo[i].philo_id];
		philo[i].sfork_id = &bill->cuttlery[(philo[i].philo_id + 1)
			% bill->philonbr];
		philo[i].nbr_lunch = 0;
		philo[i].bill = bill;
		philo[i].finish_eat = false;
		philo[i].ready = false;
		i++;
	}
	philo[bill->philonbr].philo_id = bill->philonbr;
	philo[bill->philonbr].is_waiter = true;
	philo[bill->philonbr].bill = bill;
	bill->clients = philo;
}

void	init_threads(t_bill *bill)
{
	pthread_t	*customers;
	int			i;

	i = 0;
	customers = malloc(sizeof(pthread_t) * bill->philonbr + CHECK_THREAD);
	while (i != bill->philonbr + CHECK_THREAD)
	{
		pthread_create(&customers[i], NULL,
			(void *)&exec, (void *)&bill->clients[i]);
			i++;
	}
	bill->pids = customers;
	i = 0;
	while (i != bill->philonbr + CHECK_THREAD)
	{
		pthread_join(bill->pids[i], NULL);
		i++;
	}	
}

void	init_mutex(t_bill *bill)
{
	int				i;
	pthread_mutex_t	*mutexes;

	mutexes = malloc(sizeof(pthread_mutex_t) * bill->philonbr);
	i = 0;
	while (i != bill->philonbr)
	{
		pthread_mutex_init(&mutexes[i], NULL);
		i++;
	}
	bill->cuttlery = mutexes;
}
