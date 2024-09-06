/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:04:29 by dlamark-          #+#    #+#             */
/*   Updated: 2024/09/04 21:33:36 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*routine(void *arg)
{
	t_philo			*philo;
	
	philo = (t_philo *)arg;
	while (!philo_is_dead(philo))
	{
		if (check_philo_state(philo) != -1)
		{
			if (!philo_is_dead(philo))
			{
				process_philo_thinking(philo);
			}
		}
		if (check_philo_state(philo) != -1)
		{
			if (philo->index % 2 == 0)
				process_even_philosopher_eating(philo);
			else
				process_odd_philosopher_eating(philo);
		}
		if (check_philo_state(philo) != -1)
			process_philo_sleeping(philo);
	}
	return (NULL);
}

int initialize_threads(t_philo *philo, t_dining_setup	*dinner_data)
{
	int			index;
	int			i;
	int			indexes[200];

	i = 0;
	index = dinner_data->philosophers;
	while (i < index)
	{
		indexes[i] = i;
		if (pthread_create(&philo[i].philo, NULL, &routine, &philo[indexes[i]]) != 0)
		{
			ft_putstr_fd("Error creating thread\n", 2);
			return (0);
		}
		i++;
	}
	i = 0;
	while (i < index)
	{
		pthread_join(philo[i].philo, NULL);
		i++;
	}
	return (1);
}

int	philo_is_dead(t_philo *philo)
{
	if (check_philo_state(philo) == -1)
		return (1);
	if (philo->number_of_meals == 1)
	{
		pthread_mutex_lock(&philo->monitor->notice_dead);
		printf("ta morto\n");
		philo->monitor->philo_is_dead = 1;
		pthread_mutex_unlock(&philo->monitor->notice_dead);
		return (1);
	}
	else
	{
		printf("ta vivo\n");
		return (0);
	}
}