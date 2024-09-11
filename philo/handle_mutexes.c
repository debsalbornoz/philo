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
	if (!safe_mutex_init(mutexes->print_sleep) || !safe_mutex_init(mutexes->print_think)
		|| !safe_mutex_init(mutexes->print_dead) || !safe_mutex_init(mutexes->print_eat) 
		|| !safe_mutex_init(mutexes->print_take_fork))
	{
		ft_putstr_fd("Error initializing mutex\n", 2);
		return (0);
	}
	return (1);
}