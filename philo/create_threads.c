/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:04:29 by dlamark-          #+#    #+#             */
/*   Updated: 2024/09/16 19:07:49 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	process_first_meal_routine(t_philo *philo)
{
	if (!philo_is_dead(philo) && safe_mutex_lock(&philo->check_first_meal))
	{
		if (philo->meals == 0)
		{
			if (!philo_is_dead(philo))
				process_philo_thinking(philo);
			if (!philo_is_dead(philo))
			{
				if (philo->index % 2 == 0)
					process_even_philosopher_eating(philo);
				else
					process_odd_philosopher_eating(philo);
			}
			if (!philo_is_dead(philo))
				process_philo_sleeping(philo);
		}
		safe_mutex_unlock(&philo->check_first_meal);
		return (1);
	}
	return (0);
}

int process_philo_dining(t_philo *philo)
{
	if (!philo_is_dead(philo) && safe_mutex_lock(&philo->check_first_meal))
	{
		if (philo->meals != 0)
		{
			if (!philo_is_dead(philo))
				process_philo_thinking(philo);
			if (!philo_is_dead(philo))
				process_philo_eating(philo);
			if (!philo_is_dead(philo))
				process_philo_sleeping(philo);
		}
		safe_mutex_unlock(&philo->check_first_meal);
		return (1);
	}
	return (0);
}
void *philo_routine(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	if (!process_first_meal_routine(philo))
		return (NULL);
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
				if (data->philo[i].dinner_info->start_dinner - data->philo[i].last_meal < 0)
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
	pthread_create(&monitor->monitor, NULL, &monitor_routine, data);
	while ( i < num_philos)
	{
		if (pthread_create(&philo[i].philo, NULL, &philo_routine, &philo[i]) != 0)
		{
			ft_putstr_fd("Error creating thread\n", 2);
			return 0;
		}
		i++;
	}
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