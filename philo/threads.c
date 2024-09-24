/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:04:29 by dlamark-          #+#    #+#             */
/*   Updated: 2024/09/24 18:58:41 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	initialize_threads(t_data *dinner_data)
{
	int	num_philos;

	num_philos = dinner_data->setup->philosophers;
	dinner_data->setup->start_dinner = get_time_ms();
	if (num_philos == 1)
		pthread_create(&dinner_data->philo[0].philo, NULL,
			&one_philo_routine, &dinner_data->philo[0]);
	if (num_philos > 1 && !create_philo_threads(dinner_data, num_philos))
		return (0);
	pthread_create(&dinner_data->monitor->monitor,
		NULL, &monitor_routine, dinner_data);
	pthread_join(dinner_data->monitor->monitor, NULL);
	if (!join_philo_threads(dinner_data, num_philos))
		return (0);
	return (1);
}

int	create_philo_threads(t_data *dinner_data, int num_philos)
{
	int	i;

	i = 0;
	while (num_philos > i)
	{
		if (pthread_create(&dinner_data->philo[i].philo, NULL,
				&philo_routine, &dinner_data->philo[i]) != 0)
		{
			ft_putstr_fd("Error creating thread\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}

int	join_philo_threads(t_data *dinner_data, int num_philos)
{
	int	i;

	i = 0;
	while (num_philos > i)
	{
		if (pthread_join(dinner_data->philo[i].philo, NULL) != 0)
		{
			ft_putstr_fd("Error joining threads\n", 2);
			return (0);
		}
		i++;
	}
	return (1);
}
