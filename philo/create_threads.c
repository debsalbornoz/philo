/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:04:29 by dlamark-          #+#    #+#             */
/*   Updated: 2024/09/17 21:11:57 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	process_philo_dining(t_philo *philo)
{
	if (!philo_is_dead(philo))
	{
		if (!philo_is_dead(philo))
			process_philo_thinking(philo);
		if (!philo_is_dead(philo))
		{
			if (philo->index % 2 == 0)
			{
				if (!process_even_philo_eating(philo))
					return (0);
			}
			else
			{
				if (!process_odd_philo_eating(philo))
					return (0);
			}
		}
		if (!philo_is_dead(philo))
			process_philo_sleeping(philo);
	}
	return (1);
}

void *philo_routine(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	while (!philo_is_dead(philo))
	{
		if (!process_philo_dining(philo))
			return (NULL);
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
			if (safe_mutex_lock(data->philo[i].dinner_info->nbr_of_meals))
			{
				printf("%li\n", data->philo[i].dinner_info->start_dinner);
				printf("%li\n", data->philo[i].last_meal);
				if (get_time_ms() - data->philo[i].last_meal > data->dinner_data->time_to_die)
				{
					if (safe_mutex_lock(&data->monitor->check_death))
					{
						data->monitor->death_status = 1;
						print_actions(get_time(data->dinner_data), data->philo[i].index, " is dead");
						safe_mutex_unlock(&data->monitor->check_death);
						safe_mutex_unlock(data->philo[i].dinner_info->nbr_of_meals);
						return (NULL) ;
					}
				}
				safe_mutex_unlock(data->philo[i].dinner_info->nbr_of_meals);
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

int	check_meals(t_philo *philo)
{
	if (safe_mutex_lock(philo->dinner_info->nbr_of_meals))
	{
		if (philo->meals == philo->dinner_info->number_of_meals)
			return (0);
		safe_mutex_unlock(philo->dinner_info->nbr_of_meals);
	}
	return (1);
}