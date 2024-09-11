/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:41:46 by codespace         #+#    #+#             */
/*   Updated: 2024/09/08 17:09:16 by dlamark-         ###   ########.fr       */
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
		if (!philo_is_dead(philo) && safe_mutex_lock(philo->mutexes->print_take_fork))
		{
			printf("%lu %i is taking fork\n", get_time(), philo->index);
			philo->number_of_meals += 1;
			safe_mutex_unlock(philo->mutexes->print_take_fork);
		}
	}
	if (action == EATING)
	{
		if (!philo_is_dead(philo) && safe_mutex_lock(philo->mutexes->print_eat))
		{
			printf("%lu %i is eating\n", get_time(), philo->index);
			philo->number_of_meals += 1;
			safe_mutex_unlock(philo->mutexes->print_eat);
		}
	}
}
void	safe_print(t_philo *philo, int action)
{

	if (action == SLEEPING)
	{
		if (!philo_is_dead(philo) && safe_mutex_lock(philo->mutexes->print_sleep))
		{
			printf("%lu %i is sleeping\n", get_time(), philo->index);
			usleep(3000);
			safe_mutex_unlock(philo->mutexes->print_sleep);
		}
	}
	if (action == THINKING)
	{
		if (!philo_is_dead(philo) && safe_mutex_lock(philo->mutexes->print_think))
		{
			printf("%lu %i is thinking\n", get_time(), philo->index);
			safe_mutex_unlock(philo->mutexes->print_think);
		}
	}
}
