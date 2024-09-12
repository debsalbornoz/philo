/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:41:46 by codespace         #+#    #+#             */
/*   Updated: 2024/09/12 19:39:20 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_dining_setup	dinner_data;
	t_philo			philo[200];
	pthread_mutex_t	forks[200];
	t_monitor		monitor;

	if (!validate_args(argc, argv))
		return (FALSE);
	configure_dining_parameters(&dinner_data, argv, argc);
	if (!initialize_dinner_data(&dinner_data, philo, forks, &monitor))
		return (FALSE);
}
