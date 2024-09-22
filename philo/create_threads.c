/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:04:29 by dlamark-          #+#    #+#             */
/*   Updated: 2024/09/21 21:50:38 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


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
		if (all_philos_safisfied(data))
		{
			return (NULL);
		}
		while (num_philos > i)
		{
			if (all_philos_safisfied(data))
			{
				return (NULL);
			}
			if (philo_is_dead(&data->philo[i]))
				return (NULL);
		
			i++;
		}
		i = 0;
	}
	return (NULL);
}

int	all_philos_safisfied(t_data *data)
{
	int	n_philos;
	int	i;

	n_philos = data->dinner_data->philosophers;
	i = 0;
	while (n_philos > i)
	{
		if (!is_satisfied(&data->philo[i]))
			return (0);
		i++;
	}	
	return (1);
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
