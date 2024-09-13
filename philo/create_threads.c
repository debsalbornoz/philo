/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_threads.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/28 14:04:29 by dlamark-          #+#    #+#             */
/*   Updated: 2024/09/12 21:23:01 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


/*void	*routine(void *arg)
{
	t_philo			*philo;

	philo = (t_philo *)arg;
	while (!philo_is_dead(philo))
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
		if (philo_is_dead(philo))
			break ;
	}
	return (NULL);
}
void	*monitor_routine(void *arg)
{
	t_data	*data;
	int		num_philos;
	int		i;

	data = (t_data *)arg;
	i = 0;
	num_philos = data->dinner_data->philosophers;
	printf("a\n");
	while (i < num_philos)
	{
		if (data->philo[i].number_of_meals == 1)
		{
			safe_mutex_lock(&data->philo->monitor->death_notification);
			data->philo->monitor->death_status = 1;
			print_actions(get_time(), data->philo->index, " is dead");
			pthread_mutex_unlock(&data->philo->monitor->death_notification);
			break;
		}
		i++;
		if (i == num_philos - 1)
			i = 0;
		
	}
	return (NULL);
}

int	initialize_threads(t_data *data, t_philo *philo, t_dining_setup	*dinner_data, t_monitor *monitor)
{
	int			index;
	int			i;
	int			indexes[200];

	i = 0;
	index = dinner_data->philosophers;
	while (i < index)
	{
		indexes[i] = i;
		pthread_create(&monitor->monitor, NULL, &monitor_routine, &data);
		if (pthread_create(&data->philo[i].philo, NULL,
				&routine, &philo[indexes[i]]) != 0)
		{
			ft_putstr_fd("Error creating thread\n", 2);
			return (0);
		}
		i++;
	}
	i = 0;
	printf("b\n");
	while (i < index)
	{
		pthread_join(philo[i].philo, NULL);
		i++;
	}
	pthread_join(monitor->monitor, NULL);
	return (1);
}

int	philo_is_dead(t_philo *philo)
{
	if (safe_mutex_lock(&philo->monitor->check_death))
	{
		if (philo->monitor->death_status == 1)
		{
			safe_mutex_unlock(&philo->monitor->check_death);
			return (1);
		}
		safe_mutex_unlock(&philo->monitor->check_death);
	}
	return (0);
}
*/

void *routine(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
	while (!philo_is_dead(philo))
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
			if (safe_mutex_lock(data->dinner_data->n_meals))
			{
				if (data->philo[i].number_of_meals == 1)
				{
					safe_mutex_lock(&data->monitor->death_notification);
					data->monitor->death_status = 1;
					print_actions(get_time(), data->philo[i].index, " is dead");
					safe_mutex_unlock(&data->monitor->death_notification);
					safe_mutex_unlock(data->dinner_data->n_meals);
					return (NULL);
				}	
				else
					safe_mutex_unlock(data->dinner_data->n_meals);
			}
			i++;
		}
		i = 0;
		usleep(1000);
	}
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
		if (pthread_create(&philo[i].philo, NULL, &routine, &philo[i]) != 0)
		{
			ft_putstr_fd("Error creating thread\n", 2);
			return 0;
		}
		i++;
	}
	i = 0;
	while (i < num_philos)
	{
		pthread_join(philo[i].philo, NULL);
	}
	pthread_join(monitor->monitor, NULL);
	return (1);
}

int philo_is_dead(t_philo *philo)
{
	int death_status;

	if (safe_mutex_lock(&philo->monitor->check_death))
	{
		death_status = philo->monitor->death_status;
		safe_mutex_unlock(&philo->monitor->check_death);
		return death_status == 1;
	}
	return (0);
}
