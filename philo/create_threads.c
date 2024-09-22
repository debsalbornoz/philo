/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:04:29 by dlamark-          #+#    #+#             */
/*   Updated: 2024/09/22 18:02:34 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	initialize_threads(t_data *dinner_data)
{
	int	i;
	int	num_philos;

	num_philos = dinner_data->setup->philosophers;
	dinner_data->setup->start_dinner = get_time_ms();
	i = -1;
	while (++i < num_philos)
	{
		if (pthread_create(&dinner_data->philo[i].philo, NULL,
				&philo_routine, &dinner_data->philo[i]) != 0)
		{
			ft_putstr_fd("Error creating thread\n", 2);
			return (0);
		}
	}
	pthread_create(&dinner_data->monitor->monitor,
		NULL, &monitor_routine, dinner_data);
	pthread_join(dinner_data->monitor->monitor, NULL);
	i = 0;
	while (i < num_philos)
	{
		pthread_join(dinner_data->philo[i].philo, NULL);
		i++;
	}
	return (1);
}
