/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:46:58 by codespace         #+#    #+#             */
/*   Updated: 2024/09/21 22:57:48 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	validate_args(int argc, char **argv)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	if (argc < 5 || argc > 6)
	{
		ft_putstr_fd("Invalid number of arguments\n", 2);
		return (FALSE);
	}
	if (max_n_philo(argv[1]))
		flag = 1;
	while (argv[i])
	{
		if (!is_numeric_arg(argv[i]) || is_maxmin_int(argv[i])
			|| is_negative_nbr(argv[i]))
			flag = 1;
		i++;
	}
	if (flag == 1)
		return (FALSE);
	return (TRUE);
}

int	max_n_philo(char *philos)
{
	if (ft_atol(philos) > 200)
	{
		ft_putstr_fd("Invalid number of philosophers : max number is 200\n", 2);
		return (1);
	}
	return (0);
}

int	is_numeric_arg(const char *str)
{
	while (*str)
	{
		if (!is_digit(*str))
		{
			ft_putstr_fd((char *)str, 2);
			ft_putstr_fd(" is not a valid argument :", 2);
			ft_putstr_fd(" only numeric arguments are acepted\n", 2);
			return (FALSE);
		}
		str++;
	}
	return (TRUE);
}

int	is_maxmin_int(char *str)
{
	if (ft_atol(str) >= MAX_INTEGER
		|| ft_atol(str) <= MIN_INTEGER)
	{
		ft_putstr_fd(str, 2);
		ft_putstr_fd(" : argument out of valid integer range\n", 2);
		return (TRUE);
	}
	else
		return (FALSE);
}

int	is_negative_nbr(char *str)
{
	while (*str)
	{
		if (*str == '-')
		{
			ft_putstr_fd(str, 2);
			ft_putstr_fd(" is a negative number : invalid argument", 2);
			return (1);
		}
		str++;
	}
	return (0);
}
