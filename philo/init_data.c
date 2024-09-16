/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:08:06 by codespace         #+#    #+#             */
/*   Updated: 2024/09/16 17:54:51 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <stdint.h>


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
	dinner_data->start_dinner = get_time_ms();
	safe_mutex_init(dinner_data->print_status);
	safe_mutex_init(dinner_data->update_number_of_meals);
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
		philo[i].first_meal = 0;
		i++;
	}
	safe_mutex_init(&philo->check_first_meal);
	return (philo);
}

long int	get_time_ms(void)
{
	struct timeval	tv;
	long int		time;

	gettimeofday(&tv, NULL);
	time = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	return (time);
}
long int	get_time(t_dining_setup *dinner_data)
{
	return (get_time_ms() - dinner_data->start_dinner);
}
t_monitor	*init_monitor_data(t_monitor *monitor, t_philo *philo)
{
	monitor->philos = philo;
	if (!safe_mutex_init(&monitor->check_death)
		|| !safe_mutex_init(&monitor->death_notification))
		return (NULL);
	return (monitor);
}

t_data	*initialize_data(t_data *data, t_dining_setup *dinner_data, t_philo *philo, t_monitor *monitor)
{
	data->dinner_data = dinner_data;
	data->philo = philo;
	data->monitor = monitor;
	return (data);
}