/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:30:53 by dlamark-          #+#    #+#             */
/*   Updated: 2024/09/04 21:35:33 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int take_fork(t_philo *philo, pthread_mutex_t *mutex, int flag)
{
	(void)flag;
	if (safe_mutex_lock(mutex) != 0)
		return (-1);
	else
	{
		printf("%lu %d has taken a fork\n", get_time(), philo->index);
	}
	if (safe_mutex_unlock(mutex) != 0)
		return (-1);
	return (flag);
}


void	process_even_philosopher_eating(t_philo *philo)
{
	int	flag;

	flag = 0;

	(void)flag;
	usleep(3000);
	if (check_philo_state(philo) != -1)
		take_fork(philo, philo->left_fork, flag);
	if (check_philo_state(philo) != -1)
		take_fork(philo, philo->right_fork, flag);
	if (check_philo_state(philo) != -1)
	{
		safe_print(philo, philo->mutexes->print_eat, EATING);
	}
	safe_mutex_unlock(philo->left_fork);
	safe_mutex_unlock(philo->right_fork);
}

void	process_odd_philosopher_eating(t_philo *philo)
{
	int	flag;

	flag = 0;

	if (check_philo_state(philo) != -1)
		flag += take_fork(philo, philo->right_fork, flag);
	if (check_philo_state(philo) != -1)
		flag += take_fork(philo, philo->left_fork, flag);
	printf("%i\n", flag);
	if (flag == 2 && check_philo_state(philo) != -1)
	{
		printf("chega aqui?\n");
		if (safe_print(philo, philo->mutexes->print_eat, EATING) != -1)
			philo->number_of_meals += 1;
	}
	safe_mutex_unlock(philo->right_fork);
	safe_mutex_unlock(philo->left_fork);
}

void	process_philo_thinking(t_philo	*philo)
{
	if (check_philo_state(philo) != -1)
		safe_print(philo, philo->mutexes->print_think, THINKING);
}

void	process_philo_sleeping(t_philo *philo)
{
	if (check_philo_state(philo) != -1)
	{
		if (safe_print(philo, philo->mutexes->print_sleep, SLEEPING) == -1)
			return ;
		else
			usleep(philo->dinner_info->time_to_sleep);
	}
}

int	check_philo_state(t_philo *philo)
{
	int	flag;

	flag = 0;
	pthread_mutex_lock(&philo->monitor->monitor_dead);
	if (philo->monitor->philo_is_dead == 1)
		flag = -1;
	pthread_mutex_unlock(&philo->monitor->monitor_dead);
	return (flag);
}