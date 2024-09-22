/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 20:42:52 by dlamark-          #+#    #+#             */
/*   Updated: 2024/09/21 23:58:14 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	safe_mutex_init(pthread_mutex_t *mutex)
{
	if (pthread_mutex_init(mutex, NULL) != 0)
	{
		ft_putstr_fd("Error initing mutex\n", 2);
		return (0);
	}
	return (1);
}

int	safe_mutex_lock(pthread_mutex_t *mutex)
{
	if (pthread_mutex_lock(mutex) != 0)
	{
		ft_putstr_fd("Error locking mutex\n", 2);
		return (0);
	}
	return (1);
}

int	safe_mutex_unlock(pthread_mutex_t *mutex)
{
	if (pthread_mutex_unlock(mutex) != 0)
	{
		ft_putstr_fd("Error unlocking mutex\n", 2);
		return (-1);
	}
	return (0);
}

int	safe_mutex_destroy(pthread_mutex_t *mutex)
{
	if (pthread_mutex_destroy(mutex) != 0)
	{
		ft_putstr_fd("Error destroying mutex\n", 2);
		return (-1);
	}
	return (0);
}
