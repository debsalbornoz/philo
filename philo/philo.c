/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:30:53 by dlamark-          #+#    #+#             */
/*   Updated: 2024/09/16 18:52:24 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	take_fork(t_philo *philo, pthread_mutex_t *fork)
{
	if (!philo_is_dead(philo) && safe_mutex_lock(fork))
	{
		if (safe_mutex_lock(philo->dinner_info->print_status))
		{
			if (!philo_is_dead(philo))
				print_actions(get_time(philo->dinner_info), philo->index, " is taking fork");
			safe_mutex_unlock(philo->dinner_info->print_status);
		}
		safe_mutex_unlock(fork);
		return (1);
	}
	else
		return (0);
}

void	process_even_philosopher_eating(t_philo *philo)
{
	usleep(3000);
	if (take_fork(philo, philo->left_fork))
	{
		if (take_fork(philo, philo->right_fork))
		{
			if (safe_mutex_lock(philo->dinner_info->print_status))
			{
				if (!philo_is_dead(philo) && check_meals(philo))
				{
					print_actions(get_time(philo->dinner_info), philo->index, " is eating");
					if (safe_mutex_lock(philo->dinner_info->nbr_of_meals))
					{
						philo->number_of_meals += 1;
						philo->last_meal = get_time_ms();
						safe_mutex_unlock(philo->dinner_info->nbr_of_meals);
					}
				}		
			safe_mutex_unlock(philo->dinner_info->print_status);
		}
		}
	}
}

void	process_philo_eating(t_philo *philo)
{
	if (take_fork(philo, philo->left_fork))
	{
		if (take_fork(philo, philo->right_fork))
		{
			if (safe_mutex_lock(philo->dinner_info->print_status))
			{
				if (!philo_is_dead(philo) && check_meals(philo))
				{
					print_actions(get_time(philo->dinner_info), philo->index, " is eating");
					if (safe_mutex_lock(philo->dinner_info->nbr_of_meals))
					{
						philo->number_of_meals += 1;
						philo->last_meal = get_time_ms();
						safe_mutex_unlock(philo->dinner_info->nbr_of_meals);
					}
				}		
			safe_mutex_unlock(philo->dinner_info->print_status);
		}
		}
	}
}
void	process_odd_philosopher_eating(t_philo *philo)
{
	if (take_fork(philo, philo->right_fork))
	{
		if (take_fork(philo, philo->left_fork))
		{
			if (safe_mutex_lock(philo->dinner_info->print_status))
			{
				if (!philo_is_dead(philo) && check_meals(philo))
				{
					print_actions(get_time(philo->dinner_info), philo->index, " is eating");
					if (safe_mutex_lock(philo->dinner_info->nbr_of_meals))
					{
						philo->number_of_meals += 1;
						philo->last_meal = get_time_ms();
						safe_mutex_unlock(philo->dinner_info->nbr_of_meals);
					}
				}		
			safe_mutex_unlock(philo->dinner_info->print_status);
			}
		}
	}
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
