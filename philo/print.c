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

/*void	print_philo_data(t_philo *philo, t_dining_setup	*dinner_data)
{
	int	philos;

	philos = dinner_data->philosophers;
	{
		printf("philosopher index : %i\n", philo->index);
		print_dinner_data(philo->dinner_info);
	}
}
*/

int	safe_print(t_philo *philo, pthread_mutex_t	*mutex, int flag)
{
	(void)mutex;
	if (flag == EATING)
	{
		if (pthread_mutex_lock(philo->mutexes->print_eat) != 0)
			return (-1);
		printf("%lu %i is eating\n", get_time(), philo->index);
		philo->number_of_meals += 1;
		if (pthread_mutex_unlock(philo->mutexes->print_eat) != 0)
			return (-1);
	}
	else if (flag == SLEEPING)
	{
		if (pthread_mutex_lock(philo->mutexes->print_sleep) != 0)
			return (-1);
		printf("%lu %i is sleeping\n", get_time(), philo->index);
		if (pthread_mutex_unlock(philo->mutexes->print_sleep) != 0)
			return (-1);
	}
	else if (flag == THINKING)
	{
		if (pthread_mutex_lock(philo->mutexes->print_think) != 0)
			return (-1);
		printf("%lu %i is thinking\n", get_time(), philo->index);
		if (pthread_mutex_unlock(philo->mutexes->print_think) != 0)
			return (-1);
	}
	return (0);
}