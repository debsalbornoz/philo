/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:30:53 by dlamark-          #+#    #+#             */
/*   Updated: 2024/09/22 18:10:44 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	process_philo_thinking(t_philo	*philo)
{
	if (!philo_is_dead(philo) && !philo->is_satisfied)
	{
		print_actions(get_time(philo->dinner_info), " is thinking\n", philo);
		usleep(200);
	}
	else
		return ;
}

int	process_even_philo_eating(t_philo *philo)
{
	if (!philo_is_dead(philo) && safe_mutex_lock(philo->left_fork)
		&& !philo->is_satisfied)
	{
		print_actions(get_time(philo->dinner_info), " is taking fork\n", philo);
		if (!philo_is_dead(philo) && !philo->is_satisfied)
		{
			if (philo->right_fork != NULL)
			{
				if (safe_mutex_lock(philo->right_fork))
				{
					print_actions(get_time(philo->dinner_info),
						" is taking fork\n", philo);
					if (!handle_eat(philo))
						return (0);
					safe_mutex_unlock(philo->right_fork);
				}
			}
		}
		safe_mutex_unlock(philo->left_fork);
		return (1);
	}
	else
		return (0);
}

int	process_odd_philo_eating(t_philo *philo)
{
	if (!philo_is_dead(philo) && safe_mutex_lock(philo->right_fork)
		&& !philo->is_satisfied)
	{
		print_actions(get_time(philo->dinner_info), " is taking fork\n", philo);
		if (!philo_is_dead(philo) && !philo->is_satisfied)
		{
			if (philo->right_fork != NULL)
			{
				if (safe_mutex_lock(philo->left_fork))
				{
					print_actions(get_time(philo->dinner_info),
						" is taking fork\n", philo);
					if (!handle_eat(philo))
						return (0);
					safe_mutex_unlock(philo->left_fork);
				}
			}
		}
		safe_mutex_unlock(philo->right_fork);
		return (1);
	}
	else
		return (0);
}

int	handle_eat(t_philo *philo)
{
	if (!philo_is_dead(philo) && !philo->is_satisfied)
	{
		print_actions(get_time(philo->dinner_info), " is eating\n", philo);
		philo->number_of_meals += 1;
		if (philo->number_of_meals == philo->dinner_info->number_of_meals)
		{
			philo->is_satisfied = 1;
			safe_mutex_unlock(philo->left_fork);
			safe_mutex_unlock(philo->right_fork);
			return (0);
		}
		philo->last_meal = get_time_ms();
		usleep(philo->dinner_info->time_to_eat * 1000);
	}
	return (1);
}

void	process_philo_sleeping(t_philo *philo)
{
	if (!philo_is_dead(philo) && !philo->is_satisfied)
	{
		print_actions(get_time(philo->dinner_info), " is sleeping\n", philo);
		usleep(philo->dinner_info->time_to_sleep * 1000);
	}
}
