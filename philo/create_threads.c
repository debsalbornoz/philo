/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:04:29 by dlamark-          #+#    #+#             */
/*   Updated: 2024/09/19 21:56:57 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	process_philo_dining(t_philo *philo)
{
	if (!philo_is_dead(philo))
	{
		if (!philo_is_dead(philo))
			process_philo_thinking(philo);
		if (!philo_is_dead(philo))
		{
			if (philo->index % 2 == 0)
			{
				if (!process_even_philo_eating(philo))
					return (0);
			}
			else
			{
				if (!process_odd_philo_eating(philo))
					return (0);
			}
		}
		if (!philo_is_dead(philo))
			process_philo_sleeping(philo);
	}
	return (0);
}

void *philo_routine(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	while (!philo_is_dead(philo))
	{
		if (!process_philo_dining(philo))
			return (NULL);
	}
	return (NULL);
}

void *monitor_routine(void *arg)
{
	t_data	*data;
	int		num_philos;
	int		i;
	
	data = (t_data *)arg;
	num_philos = data->dinner_data->philosophers;
	i = 0;
	while (1)
	{
		while (num_philos > i)
		{
			if (!philo_is_dead(&data->philo[i]))
				return (0);
		
			i++;
		}
		i = 0;
	}
	return (NULL);
}


int initialize_threads(t_data *data, t_philo *philo, t_dining_setup *dinner_data, t_monitor *monitor)
{
	int i;
	int num_philos;
	
	num_philos = dinner_data->philosophers;
	i = 0;
	while ( i < num_philos)
	{
		if (pthread_create(&philo[i].philo, NULL, &philo_routine, &philo[i]) != 0)
		{
			ft_putstr_fd("Error creating thread\n", 2);
			return 0;
		}
		i++;
	}
	pthread_create(&monitor->monitor, NULL, &monitor_routine, data);
	pthread_join(monitor->monitor, NULL);
	i = 0;
	while (i < num_philos)
	{
		pthread_join(philo[i].philo, NULL);
		i++;
	}
	return (1);
}

int philo_is_dead(t_philo *philo)
{
    long int time;

    pthread_mutex_lock(&philo->monitor->monitor_philo);
	time = get_time(philo->dinner_info);
	printf("time %li: \n", time);
	printf(" last meal : %li\n", philo->last_meal);
	printf("time - last meal: %li\n",time - philo->last_meal);
	printf("time to die: %li \n", philo->dinner_info->time_to_die);
	if (get_time_ms() - philo->last_meal > philo->dinner_info->time_to_die)
	{
		printf("chega aqui?\n");
		philo->monitor->death_status = 1;
		ft_putstr_fd("died\n", 1);
		if (pthread_mutex_unlock(&philo->monitor->monitor_philo) != 0)
			return (-1);
		return (1);
	}
	pthread_mutex_unlock(&philo->monitor->monitor_philo);
	return (0);
}

int	check_meals(t_philo *philo)
{
	if (safe_mutex_lock(&philo->monitor->monitor_philo))
	{
		if (philo->number_of_meals == philo->dinner_info->number_of_meals)
			return (0);
		safe_mutex_unlock(&philo->monitor->monitor_philo);
	}
	return (1);
}