/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:04:29 by dlamark-          #+#    #+#             */
/*   Updated: 2024/09/22 18:10:10 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo_is_dead(philo) || philo->is_satisfied)
	{
		process_philo_thinking(philo);
		if (philo->index % 2 == 0)
		{
			if (!process_even_philo_eating(philo))
				return (NULL);
		}
		else
		{
			if (!process_odd_philo_eating(philo))
				return (NULL);
		}	
		process_philo_sleeping(philo);
	}
	return (NULL);
}

void	*one_philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (!philo_is_dead(philo) || philo->is_satisfied)
	{
		process_philo_thinking(philo);
		if (!philo_is_dead(philo))
			process_philo_eating(philo);
		if (!philo_is_dead(philo))
			process_philo_sleeping(philo);
	}
	return (NULL);
}

int	process_philo_eating(t_philo *philo)
{
	while (!philo_is_dead(philo))
	{
		safe_mutex_lock(philo->left_fork);
		print_actions(get_time(philo->dinner_info), " is taking fork\n", philo);
		usleep(philo->dinner_info->time_to_die * 1000);
		safe_mutex_unlock(philo->left_fork);
	}
	return (0);
}