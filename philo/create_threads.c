/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:04:29 by dlamark-          #+#    #+#             */
/*   Updated: 2024/09/13 17:41:11 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *routine(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	while (!philo_is_dead(philo))
	{
		if (!philo_is_dead(philo))
			process_philo_thinking(philo);
		if (!philo_is_dead(philo))
		{
			if (philo->index % 2 == 0)
				process_even_philosopher_eating(philo);
			else
				process_odd_philosopher_eating(philo);
		}
		if (!philo_is_dead(philo))
			process_philo_sleeping(philo);
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
		while ( i < num_philos)
		{
			if (data->philo[i].number_of_meals == 1)
			{
				if (safe_mutex_lock(&data->monitor->death_notification))
				{
					data->monitor->death_status = 1;
					print_actions(get_time(), data->philo[i].index, " is dead");
					safe_mutex_unlock(&data->monitor->death_notification);
					return (NULL) ;
				}
			}	
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
	pthread_create(&monitor->monitor, NULL, &monitor_routine, data);
	while ( i < num_philos)
	{
		if (pthread_create(&philo[i].philo, NULL, &routine, &philo[i]) != 0)
		{
			ft_putstr_fd("Error creating thread\n", 2);
			return 0;
		}
		i++;
	}
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
	if (safe_mutex_lock(&philo->monitor->check_death))
	{
		if (philo->monitor->death_status == 1)
		{
			safe_mutex_unlock(&philo->monitor->check_death);
			return (1);
		}
		else
		{
			safe_mutex_unlock(&philo->monitor->check_death);
			return (0);
		}
	}
	return (0);
}