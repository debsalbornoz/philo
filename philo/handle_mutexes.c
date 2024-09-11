/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_mutexes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 18:29:49 by dlamark-          #+#    #+#             */
/*   Updated: 2024/09/11 20:32:11 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	initialize_mutexes(t_mutexes *mutexes)
{
	if (!safe_mutex_init(mutexes->print))
	{
		ft_putstr_fd("Error initializing mutex\n", 2);
		return (0);
	}
	return (1);
}