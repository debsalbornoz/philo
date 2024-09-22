/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:04:29 by dlamark-          #+#    #+#             */
/*   Updated: 2024/09/21 23:51:47 by dlamark-         ###   ########.fr       */
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

int	is_satisfied(t_philo *philo)
{
	if (philo->is_satisfied == 1)
		return (1);
	return (0);
}