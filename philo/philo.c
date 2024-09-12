/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:30:53 by dlamark-          #+#    #+#             */
/*   Updated: 2024/09/11 21:14:41 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int take_fork(t_philo *philo, pthread_mutex_t *fork)
{
	if (!philo_is_dead(philo) && safe_mutex_lock(fork))
	{
		safe_print_eat(philo, TAKING_FORK);
		safe_mutex_unlock(fork);
		return (1);
	}
	else
		return (0);
}


void	process_even_philosopher_eating(t_philo *philo)
{
	usleep(3000);
	if (!philo_is_dead(philo) && take_fork(philo, philo->left_fork))
	{
		if (!philo_is_dead(philo) && take_fork(philo, philo->right_fork))
		{
			safe_print_eat(philo, EATING);
			//safe_mutex_unlock(philo->left_fork);
			//safe_mutex_unlock(philo->right_fork);
		}
		//else
			//safe_mutex_unlock(philo->left_fork);
	}
}


void	process_odd_philosopher_eating(t_philo *philo)
{
	if (!philo_is_dead(philo) && take_fork(philo, philo->right_fork))
	{
		if (!philo_is_dead(philo) && take_fork(philo, philo->left_fork))
		{
			safe_print_eat(philo, EATING);
			//safe_mutex_unlock(philo->right_fork);
			//safe_mutex_unlock(philo->left_fork);
		}
		//else
			//safe_mutex_unlock(philo->right_fork);
	}
}

void	process_philo_thinking(t_philo	*philo)
{
	if (!philo_is_dead(philo))
		safe_print(philo, THINKING);
	else
		return ;
}

void	process_philo_sleeping(t_philo *philo)
{
	if (!philo_is_dead(philo))
		safe_print(philo, SLEEPING);
}
