/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:41:46 by codespace         #+#    #+#             */
/*   Updated: 2024/09/11 21:11:51 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_dinner_data(t_dining_setup *dinner_data)
{
	printf("num of philo: %ld\n", dinner_data->philosophers);
	printf("num of forks: %ld\n", dinner_data->n_forks);
	printf("time to die: %ld\n", dinner_data->time_to_die);
	printf("time to eat: %ld\n", dinner_data->time_to_eat);
	printf("time to sleep: %ld\n", dinner_data->time_to_sleep);
	printf("number of meals: %d\n", dinner_data->number_of_meals);
	printf("start dinner: %ld\n", dinner_data->start_dinner);
}
void	safe_print_eat(t_philo *philo, int action)
{
	if (action == TAKING_FORK)
	{
		if (!philo_is_dead(philo) && safe_mutex_lock(philo->mutexes->print))
		{
			if (!philo_is_dead(philo))
			ft_putstr_fd("is taking fork \n", 1);
			safe_mutex_unlock(philo->mutexes->print);
		}
	}
	if (action == EATING)
	{
		if (!philo_is_dead(philo) && safe_mutex_lock(philo->mutexes->print))
		{
			if (!philo_is_dead(philo))
			{
				ft_putstr_fd("is eating\n", 1);
				philo->number_of_meals += 1;
			}		
			safe_mutex_unlock(philo->mutexes->print);
		}
	}
}

void	safe_print(t_philo *philo, int action)
{

	if (action == SLEEPING)
	{
		if (!philo_is_dead(philo) && safe_mutex_lock(philo->mutexes->print))
		{
			if (!philo_is_dead(philo))
			{
				ft_putstr_fd("is sleeping \n",1);
				usleep(philo->dinner_info->time_to_sleep);
			}
			safe_mutex_unlock(philo->mutexes->print);
		}
	}
	if (action == THINKING)
	{
		if (!philo_is_dead(philo) && safe_mutex_lock(philo->mutexes->print))
		{
			if (!philo_is_dead(philo))
				ft_putstr_fd("is thinking\n",1);
			safe_mutex_unlock(philo->mutexes->print);
		}
	}
}
