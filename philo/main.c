/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:41:46 by codespace         #+#    #+#             */
/*   Updated: 2024/09/01 17:07:15 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_dining_setup	dinner_data;
	t_philo			philo[200];
	pthread_mutex_t	forks[200];
	t_mutexes		mutexes;
	t_monitor		monitor;
	
	if (!validate_args(argc, argv))
		return (FALSE);
	configure_dining_parameters(&dinner_data, argv, argc);
	if (!initialize_dinner_data(&dinner_data, philo, forks, &mutexes, &monitor))
		return (FALSE);
}
