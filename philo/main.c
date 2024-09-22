/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:41:46 by codespace         #+#    #+#             */
/*   Updated: 2024/09/21 23:59:14 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_dining_setup	dinner_data;
	t_philo			philo[200];
	pthread_mutex_t	forks[200];
	t_monitor		monitor;
	t_data			data;

	if (!validate_args(argc, argv))
		return (FALSE);
	configure_dining_parameters(&dinner_data, argv, argc);
	if (!initialize_forks(forks, &dinner_data)
		|| !initialize_philo_data(&dinner_data, philo, forks, &monitor)
		|| !init_monitor_data(&monitor, philo)
		|| !initialize_data(&data, &dinner_data, philo, &monitor)
		|| !initialize_threads(&data, philo, &dinner_data, &monitor))
		return (FALSE);
}
