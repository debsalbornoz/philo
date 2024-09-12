/* ************************************************************************** */
/*			                                                                */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: codespace <codespace@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:48:19 by codespace         #+#    #+#             */
/*   Updated: 2024/07/24 18:20:42 by codespace        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_actions(long int time, int philo_index, char *action)
{
	char simulation_time[25];
	char index[3];

	ft_itoa(time, simulation_time, sizeof(simulation_time));
	ft_itoa((long int)philo_index, index, sizeof(index));
	ft_putstr_fd(simulation_time, 1);
	ft_putstr_fd(" ", 1);
	ft_putstr_fd(index, 1);
	ft_putstr_fd(action, 1);
	ft_putstr_fd("\n", 1);

}

void	ft_putstr_fd(const char *str, int fd)
{
	int	len;

	len = ft_strlen((char *)str);
	write(fd, str, len);
}


static int	get_digits(long int nbr)
{
	unsigned int counter = 1;
	
	if (nbr < 0)
		nbr = nbr * -1;
	while (nbr > 9)
	{
		nbr = nbr / 10;
		counter++;
	}
	return (counter);
}

void ft_itoa(long int n, char *str, size_t buffer_size)
{
    long int num = n;
    size_t num_digits;
    int is_negative = 0;

    if (n == 0)
    {
        if (buffer_size > 1)
        {
            str[0] = '0';
            str[1] = '\0';
        }
        return;
    }
    if (n < 0)
    {
        is_negative = 1;
        num = -num;
    }
    num_digits = get_digits(num);
    if (is_negative)
        num_digits++;
    if (buffer_size <= num_digits)
    {
        str[0] = '\0';
        return;
    }
    if (is_negative)
    {
        str[num_digits - 1] = '\0';
        num_digits--;
        str[0] = '-';
    }
    else
        str[num_digits] = '\0';
    while (num_digits > 0)
    {
        str[--num_digits] = (num % 10) + '0';
        num /= 10;
    }
}
