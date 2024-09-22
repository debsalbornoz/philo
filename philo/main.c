/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 13:41:46 by codespace         #+#    #+#             */
/*   Updated: 2024/09/22 17:59:52 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	start_dinner(t_data *dinner_data);

int	main(int argc, char **argv)
{
	t_data			dinner_data;

	if (!validate_args(argc, argv))
		return (FALSE);
	configure_dining_parameters(&dinner_data, argc, argv);
	if (!start_dinner(&dinner_data))
		return (FALSE);
	return (TRUE);
}
