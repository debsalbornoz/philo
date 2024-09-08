/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:08:06 by codespace         #+#    #+#             */
/*   Updated: 2024/09/08 17:14:55 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdint.h>


int initialize_dinner_data(t_dining_setup *dinner_data, t_philo *philo, pthread_mutex_t *forks, t_mutexes *mutexes, t_monitor *monitor)
{
	if (!initialize_forks(forks, dinner_data) || !initialize_mutexes(mutexes)
			|| !initialize_philo_data(dinner_data, philo, forks, mutexes, monitor) || !initialize_threads(philo, dinner_data))
		return (0);
	else
		return (1);
}

void	configure_dining_parameters(t_dining_setup *dinner_data,
char **argv, int argc)
{
	dinner_data->philosophers = ft_atol(argv[1]);
	dinner_data->n_forks = ft_atol(argv[1]);
	dinner_data->time_to_die = ft_atol(argv[2]);
	dinner_data->time_to_eat = ft_atol(argv[3]);
	dinner_data->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		dinner_data->number_of_meals = ft_atol(argv[5]);
	else
		dinner_data->number_of_meals = -1;
	dinner_data->start_dinner = get_time();
}

t_philo *initialize_philo_data(t_dining_setup	*dinner_data, t_philo *philo, pthread_mutex_t *forks, t_mutexes *mutexes, t_monitor *monitor)
{
	int				n_philo;
	int				i;

	n_philo = dinner_data->philosophers;
	i = 0;
	while (i < n_philo)
	{
		philo[i].index = i;
		philo[i].dinner_info = dinner_data;
		assign_forks(philo, i , n_philo, forks);
		philo[i].mutexes = mutexes;
		philo[i].number_of_meals = 0;
		philo[i].monitor = monitor;
		i++;
	}
	if (safe_mutex_init(&monitor->monitor_dead) == -1)
	{
		printf("a\n");
	}
	if (safe_mutex_init(&monitor->notice_dead) == -1)
		printf("b\n");
	if (safe_mutex_init(&monitor->flag) == -1)
		return (NULL);
	return(philo);
}

long int get_time(void)
{
	struct timeval tv;
	long int time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + ( tv.tv_usec / 1000);
	return (time);
}


/*void	assign_prints(pthread_mutex_t *prints, t_philo *philo, t_dining_setup *dinner_data)
{		
	int	i;
	int	n_philos;
	int	j;
	
	i = 0;
	j = 0;
	n_philos = dinner_data->philosophers;	
	while(j < n_philos * 2)
	{
		philo[i].print_sleep = &prints[j];
		j++;
		philo[i].print_think = &prints[j];
		j++;
		i++;#include "philo.h"
#include <stdint.h>


int initialize_dinner_data(t_dining_setup *dinner_data, t_philo *philo, pthread_mutex_t *forks, t_mutexes *mutexes)
{
	if (!initialize_forks(forks, dinner_data) || !initialize_mutexes(mutexes)
			|| !initialize_philo_data(dinner_data, philo, forks, mutexes) || !initialize_threads(philo, dinner_data))
		return (0);
	else
		return (1);
}

void	configure_dining_parameters(t_dining_setup *dinner_data,
char **argv, int argc)
{
	
	dinner_data->philosophers = ft_atol(argv[1]);
	dinner_data->n_forks = ft_atol(argv[1]);
	dinner_data->time_to_die = ft_atol(argv[2]) * 1000;
	dinner_data->time_to_eat = ft_atol(argv[3]) * 1000;
	dinner_data->time_to_sleep = ft_atol(argv[4]) * 1000;
	if (argc == 6)
		dinner_data->number_of_meals = ft_atol(argv[5]);
	else
		dinner_data->number_of_meals = -1;
	dinner_data->start_dinner = get_time();
}

long int	get_time(void)
{
	struct timeval tv;
	long int		time;
	
	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 100000 + tv.tv_usec;
	return(time);
}
*/
/*
void	assign_prints(pthread_mutex_t *prints, t_philo *philo, t_dining_setup *dinner_data)
{		
	int	i;
	int	n_philos;
	int	j;
	
	i = 0;
	j = 0;
	n_philos = dinner_data->philosophers;	
	while(j < n_philos * 2)
	{
		philo[i].print_sleep = &prints[j];
		j++;
		philo[i].print_think = &prints[j];
		j++;
		i++;
	}
}
*/
