/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:30:53 by dlamark-          #+#    #+#             */
/*   Updated: 2024/09/19 22:00:38 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	handle_eat(t_philo *philo);

int	process_even_philo_eating(t_philo *philo)
{
	if (!philo_is_dead(philo) && safe_mutex_lock(philo->left_fork))
	{
		if (!philo_is_dead(philo) && safe_mutex_lock(philo->right_fork))
		{
			print_actions(get_time(philo->dinner_info), philo->index, " is taking fork", philo);
			if (!handle_eat(philo))
			{
				safe_mutex_unlock(philo->right_fork);
				return (0);
			}
			safe_mutex_unlock(philo->right_fork);
		}
		safe_mutex_unlock(philo->left_fork);
		return (1);
	}
	else
		return (0);
}
int	process_odd_philo_eating(t_philo *philo)
{
	if (!philo_is_dead(philo) && safe_mutex_lock(philo->right_fork))
	{
		if (!philo_is_dead(philo) && safe_mutex_lock(philo->left_fork))
		{
			print_actions(get_time(philo->dinner_info), philo->index, " is taking fork", philo);
			if (!handle_eat(philo))
			{
				safe_mutex_unlock(philo->left_fork);				
				return (0);
			}
			safe_mutex_unlock(philo->left_fork);
		}
		safe_mutex_unlock(philo->right_fork);
		return (1);
	}
	else
		return (0);
}

int	handle_eat(t_philo *philo)
{
	if (!philo_is_dead(philo))
	{
		if (!check_meals(philo))
			return (0);
		print_actions(get_time(philo->dinner_info), philo->index, " is eating", philo);
		if (safe_mutex_lock(&philo->monitor->monitor_philo))
		{
			philo->number_of_meals += 1;
			usleep(philo->dinner_info->time_to_eat);
			philo->last_meal = get_time(philo->dinner_info);
			safe_mutex_unlock(&philo->monitor->monitor_philo);
		}
	}
	return (1);
}

void	process_philo_thinking(t_philo	*philo)
{
	if (!philo_is_dead(philo))
		print_actions(get_time(philo->dinner_info), philo->index, " is thinking", philo);
	else
		return ;
}

void	process_philo_sleeping(t_philo *philo)
{
	if (!philo_is_dead(philo))
	{
		print_actions(get_time(philo->dinner_info), philo->index, " is sleeping", philo);
		usleep(philo->dinner_info->time_to_sleep);
	}
}
