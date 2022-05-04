/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith <jsmith@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/20 18:05:51 by jsmith            #+#    #+#             */
/*   Updated: 2022/05/04 18:06:32 by jsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>
# define CHECK_THREAD 1
# define AVOID 1
# define STD_WAIT 50

typedef struct s_filo
{
	int					philo_id;
	pthread_t			*pids;
	pthread_mutex_t		*ffork_id;
	pthread_mutex_t		*sfork_id;
	pthread_mutex_t		write_permission;
	int					last_lunch;
	bool				my_turn;
	bool				is_dead;
	int					last_eat;
	struct s_bill		*bill;
	bool				is_waiter;
	bool				ready;
	int					nbr_lunch;
	bool				init;
	bool				finish_eat;

}		t_philo;

typedef struct s_bill
{
	int						philonbr;
	long long				life_long;
	long long				eat_long;
	long long				sleep_long;
	long long				first_timestamp;
	int						max_eat;
	bool					corpse_404;
	bool					flag;
	pthread_t				*pids;
	t_philo					*clients;
	pthread_mutex_t			*cuttlery;
	int						finished;
}	t_bill;

void		init_clients(t_bill *bill);
void		init_bill(int argc, char *argv[], t_bill *bill);
int			ft_atoi(const char *str);
long long	refresh_time(void);
long long	time_diff(long long start, long long last);
void		own_usleep(long long m_usleep);
void		assing_utils_to_philos(t_bill *bill);
void		*exec(void *uknown);
void		*syncronyze_threads(t_philo *philo);
void		lock_print_unlock(char *philo_action, t_philo *philo);
bool		philo_eats(t_philo *philo);
bool		philo_forks_impar(t_philo *philo);
bool		philo_forks(t_philo *philo);
bool		philo_sleeps(t_philo *philo);
bool		philo_thinks(t_philo *philo);
void		init_threads(t_bill *bill);
void		init_mutex(t_bill *bill);
bool		normative_check(t_philo *philo);
int			ft_isdigit(int c);
bool		check_digit(char *argv[]);
bool		must_die(t_philo *philo);
#endif