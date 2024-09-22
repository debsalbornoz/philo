/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/19 18:21:21 by dlamark-          #+#    #+#             */
/*   Updated: 2024/09/21 23:56:10 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	get_time_ms(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
	{
		ft_putstr_fd("Error\n", 2);
		return (0);
	}
	return ((tv.tv_sec * (unsigned int)1000) + (tv.tv_usec / 1000));
}

unsigned int	get_time(t_dining_setup *dinner_data)
{
	long int	current_time;
	long int	start_dinner;

	current_time = get_time_ms();
	start_dinner = dinner_data->start_dinner;
	return (current_time - start_dinner);
}
