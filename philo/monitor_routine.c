/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/21 22:56:28 by dlamark-          #+#    #+#             */
/*   Updated: 2024/09/21 23:59:03 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*monitor_routine(void *arg)
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
			{
				return (NULL);
			}
			i++;
		}
		i = 0;
	}
	return (NULL);
}

int	philo_is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->monitor->monitor_philo);
	if (philo->monitor->death_status == 1)
	{
		pthread_mutex_unlock(&philo->monitor->monitor_philo);
		return (1);
	}
	if (get_time_ms() - philo->last_meal > philo->dinner_info->time_to_die
		&& !is_satisfied(philo))
	{
		philo->monitor->death_status = 1;
		pthread_mutex_unlock(&philo->monitor->monitor_philo);
		printf("%u %i is dead\n", get_time(philo->dinner_info), philo->index);
		return (1);
	}
	pthread_mutex_unlock(&philo->monitor->monitor_philo);
	return (0);
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
