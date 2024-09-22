/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:28:59 by dlamark-          #+#    #+#             */
/*   Updated: 2024/09/22 16:58:02 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

pthread_mutex_t	*initialize_forks(t_data *dinner_data)
{
	int				n_forks;
	int				i;

	n_forks = dinner_data->setup->n_forks;
	i = 0;
	while (n_forks > i)
	{
		if (pthread_mutex_init(&dinner_data->forks[i], NULL) != 0)
		{
			ft_putstr_fd("Error initializing mutex\n", 2);
			return (NULL);
		}
		i++;
	}
	return (dinner_data->forks);
}

void	assign_forks(t_philo *philo, int i, int n_philo, pthread_mutex_t *forks)
{
	if (n_philo == 1)
	{
		philo[i].left_fork = &forks[i];
		philo[i].right_fork = NULL;
	}
	if (i == n_philo -1)
	{
		philo[i].left_fork = &forks[i];
		philo[i].right_fork = &forks[0];
	}
	else
	{
		philo[i].left_fork = &forks[i];
		philo[i].right_fork = &forks[i + 1];
	}
}