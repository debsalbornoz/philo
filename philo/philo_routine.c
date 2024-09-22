/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:04:29 by dlamark-          #+#    #+#             */
/*   Updated: 2024/09/21 21:50:21 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philo_routine(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	while (!philo_is_dead(philo) || !is_satisfied(philo))
	{
		process_philo_thinking(philo);
		if (!process_philo_eating(philo))
			return (NULL);
		process_philo_sleeping(philo);
	}
	return (NULL);
}


int philo_is_dead(t_philo *philo)
{

	pthread_mutex_lock(&philo->monitor->monitor_philo);
	if (philo->monitor->death_status == 1)
	{
		pthread_mutex_unlock(&philo->monitor->monitor_philo);
		return (1);
	}
	if (get_time_ms() - philo->last_meal > philo->dinner_info->time_to_die && !is_satisfied(philo))
	{
		philo->monitor->death_status = 1;
		pthread_mutex_unlock(&philo->monitor->monitor_philo);
		printf("%u %i is dead\n", get_time(philo->dinner_info), philo->index);
		return (1);
	}
	pthread_mutex_unlock(&philo->monitor->monitor_philo);
	return (0);
}

int	is_satisfied(t_philo *philo)
{
	if (philo->is_satisfied == 1)
		return (1);
	return (0);
}