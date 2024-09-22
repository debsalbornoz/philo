/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:41:46 by codespace         #+#    #+#             */
/*   Updated: 2024/09/22 17:42:23 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_data			dinner_data;

	if (!validate_args(argc, argv))
		return (FALSE);
	configure_dining_parameters(&dinner_data, argc, argv);
	initialize_forks(&dinner_data);
	initialize_philo_data(&dinner_data);
	init_monitor_data(&dinner_data);
	initialize_threads(&dinner_data);
	/*if (!initialize_forks(&)
		|| !initialize_philo_data(&dinner_data, philo, forks, &monitor)
		|| !init_monitor_data(&monitor, philo)
		|| !initialize_data(&data, &dinner_data, philo, &monitor)
		|| !initialize_threads(&data, philo, &dinner_data, &monitor))
	*/
		return (FALSE);
}
