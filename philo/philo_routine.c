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

void *philo_routine(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	while (!philo_is_dead(philo))
	{
		process_philo_thinking(philo);
        process_philo_eating(philo);
		process_philo_sleeping(philo);
	}
	return (NULL);
}


int philo_is_dead(t_philo *philo)
{
    pthread_mutex_lock(&philo->monitor->monitor_philo);
	if (get_time_ms() - philo->last_meal > philo->dinner_info->time_to_die)
	{
		philo->monitor->death_status = 1;
		//print_actions(get_time(philo->dinner_info), philo->index, "is dead\n", philo);
		if (pthread_mutex_unlock(&philo->monitor->monitor_philo) != 0)
			return (-1);
		return (1);
	}
	usleep(5);
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
