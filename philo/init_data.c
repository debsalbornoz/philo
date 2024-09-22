/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/25 11:08:06 by codespace         #+#    #+#             */
/*   Updated: 2024/09/22 18:00:08 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	configure_dining_parameters(t_data *dinner_data,
int argc, char **argv)
{
	dinner_data->setup->philosophers = ft_atol(argv[1]);
	dinner_data->setup->n_forks = ft_atol(argv[1]);
	dinner_data->setup->time_to_die = ft_atol(argv[2]);
	dinner_data->setup->time_to_eat = ft_atol(argv[3]);
	dinner_data->setup->time_to_sleep = ft_atol(argv[4]);
	if (argc == 6)
		dinner_data->setup->number_of_meals = ft_atol(argv[5]);
	else
		dinner_data->setup->number_of_meals = -1;
	dinner_data->setup->start_dinner = get_time_ms();
}

int	start_dinner(t_data *dinner_data)
{
	if (!initialize_forks(dinner_data)
		|| !initialize_philo_data(dinner_data)
		|| !init_monitor_data(dinner_data)
		|| !initialize_threads(dinner_data))
		return (0);
	return (1);
}

t_philo	*initialize_philo_data(t_data *dinner_data)
{
	int				n_philo;
	int				i;

	n_philo = dinner_data->setup->philosophers;
	i = 0;
	while (i < n_philo)
	{
		dinner_data->philo[i].index = i;
		dinner_data->philo[i].dinner_info = dinner_data->setup;
		assign_forks(dinner_data->philo, i, n_philo, dinner_data->forks);
		dinner_data->philo[i].number_of_meals = 0;
		dinner_data->philo[i].monitor = dinner_data->monitor;
		dinner_data->philo[i].is_satisfied = 0;
		dinner_data->philo[i].last_meal
			= dinner_data->philo[i].dinner_info->start_dinner;
		i++;
	}
	safe_mutex_init(&dinner_data->philo->check_first_meal);
	return (dinner_data->philo);
}

t_monitor	*init_monitor_data(t_data *dinner_data)
{
	dinner_data->monitor->philos = dinner_data->philo;
	if (!safe_mutex_init(&dinner_data->monitor->monitor_philo)
		|| !safe_mutex_init(&dinner_data->monitor->print_status))
		return (NULL);
	return (dinner_data->monitor);
}
