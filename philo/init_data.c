/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:08:06 by codespace         #+#    #+#             */
/*   Updated: 2024/09/12 19:40:41 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdint.h>

int	initialize_dinner_data(t_dining_setup *dinner_data, t_philo *philo,
	pthread_mutex_t *forks, t_monitor *monitor)
{
	if (!initialize_forks(forks, dinner_data) 
		|| !initialize_philo_data(dinner_data, philo, forks, monitor)
		|| !initialize_threads(philo, dinner_data)
		|| !init_monitor_data(monitor, philo))
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
	safe_mutex_init(dinner_data->print_status);
}

t_philo	*initialize_philo_data(t_dining_setup	*dinner_data, t_philo *philo,
	pthread_mutex_t *forks, t_monitor *monitor)
{
	int				n_philo;
	int				i;

	n_philo = dinner_data->philosophers;
	i = 0;
	while (i < n_philo)
	{
		philo[i].index = i;
		philo[i].dinner_info = dinner_data;
		assign_forks(philo, i, n_philo, forks);
		philo[i].number_of_meals = 0;
		philo[i].monitor = monitor;
		i++;
	}
	return (philo);
}

long int	get_time(void)
{
	struct timeval	tv;
	long int		time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}

t_monitor	*init_monitor_data(t_monitor *monitor, t_philo *philo)
{
	monitor->philos = philo;
	if (!safe_mutex_init(&monitor->check_death)
		|| !safe_mutex_init(&monitor->death_notification))
		return (NULL);
	return (monitor);
}
