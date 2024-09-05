/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mutexes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:29:49 by dlamark-          #+#    #+#             */
/*   Updated: 2024/09/04 20:14:35 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	initialize_mutexes(t_mutexes *mutexes)
{
	int	flag;

	flag = 0;
	if (pthread_mutex_init(mutexes->print_sleep, NULL) != 0)
		flag = 1;
	if (pthread_mutex_init(mutexes->print_think, NULL) != 0)
		flag = 1;
	if (pthread_mutex_init(mutexes->print_dead, NULL) != 0)
		flag = 1;
	if (pthread_mutex_init(mutexes->print_eat, NULL) != 0)
		flag = 1;		
	if (flag == 1)
	{
		ft_putstr_fd("Error initializing mutex\n", 2);
		return (0);
	}
	return (1);
}