/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:30:53 by dlamark-          #+#    #+#             */
/*   Updated: 2024/09/17 21:11:30 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	handle_eat(t_philo *philo);

int	process_even_philo_eating(t_philo *philo)
{
	if (!philo_is_dead(philo) && safe_mutex_lock(philo->left_fork))
	{
		if (safe_mutex_lock(philo->right_fork))
		{
			if (safe_mutex_lock(philo->dinner_info->print_status))
			{
				if (!philo_is_dead(philo))
					print_actions(get_time(philo->dinner_info), philo->index, " is taking fork");
				if (!handle_eat(philo))
					return (0);
				safe_mutex_unlock(philo->dinner_info->print_status);
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
		if (safe_mutex_lock(philo->left_fork))
		{
			if (safe_mutex_lock(philo->dinner_info->print_status))
			{
				if (!philo_is_dead(philo))
					print_actions(get_time(philo->dinner_info), philo->index, " is taking fork");
				if (!handle_eat(philo))
					return (0);
				safe_mutex_unlock(philo->dinner_info->print_status);
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
		print_actions(get_time(philo->dinner_info), philo->index, " is eating");
		if (safe_mutex_lock(philo->dinner_info->nbr_of_meals))
		{
			philo->number_of_meals += 1;
			usleep(philo->dinner_info->time_to_eat);
			philo->last_meal = get_time_ms();
			safe_mutex_unlock(philo->dinner_info->nbr_of_meals);
		}
	}
	return (1);
}

void	process_philo_thinking(t_philo	*philo)
{
	if (safe_mutex_lock(philo->dinner_info->print_status))
	{
		if (!philo_is_dead(philo))
			print_actions(get_time(philo->dinner_info), philo->index, " is thinking");
		safe_mutex_unlock(philo->dinner_info->print_status);
	}
	else
		return ;
}

void	process_philo_sleeping(t_philo *philo)
{
	if (safe_mutex_lock(philo->dinner_info->print_status))
	{
		if (!philo_is_dead(philo))
		{
			print_actions(get_time(philo->dinner_info), philo->index, " is sleeping");
			usleep(philo->dinner_info->time_to_sleep);
		}
		safe_mutex_unlock(philo->dinner_info->print_status);
		}		
	}
