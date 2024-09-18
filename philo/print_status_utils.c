/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:48:19 by codespace         #+#    #+#             */
/*   Updated: 2024/09/17 19:33:42 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_memcpy(void *dest, const void *src, int n);

void print_actions(long int time, int philo_index, char *action)
{
	char	time_str[25];
	char	index_str[10];
	char	buffer[256];
	int		total_len;
	int		offset;

	offset = 0;
	ft_itoa(time, time_str, sizeof(time_str), 0 );
	ft_itoa(philo_index, index_str, sizeof(index_str), 0);
	total_len = ft_strlen(time_str) + ft_strlen(index_str) + ft_strlen(action) + 3;
	if ((long unsigned int) total_len >= sizeof(buffer))
		return ; 
	ft_memcpy(buffer + offset, time_str, ft_strlen(time_str));
	offset += ft_strlen(time_str);
	buffer[offset++] = ' ';
	ft_memcpy(buffer + offset, index_str, ft_strlen(index_str));
	offset += ft_strlen(index_str);
	ft_memcpy(buffer + offset, action, ft_strlen(action));
	offset += ft_strlen(action);
	buffer[offset++] = '\n';
	write(1, buffer, offset);
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


void ft_itoa(long int n, char *str, size_t buffer_size, int is_negative)
{
	long int num;
	int num_digits;

	is_negative = 0;
	num = n;
	if (num < 0)
	{
		is_negative = 1;
		num = -num;
	}
	num_digits = get_digits(num);
	if (is_negative)
		num_digits++;
	if (buffer_size <= (size_t)num_digits)
	{ 
		str[0] = '\0';
		return;
	}
	str[num_digits] = '\0';
	if (is_negative) str[0] = '-';
	while (num_digits > is_negative)
	{
		str[--num_digits] = (num % 10) + '0';
		num /= 10;
	}
}

void	*ft_memcpy(void *dest, const void *src, int n)
{
	unsigned char *psrc; 
	unsigned char *pdest;
	int i;

	psrc = (unsigned char *)src; 
	pdest = (unsigned char *)dest;
	i = 0;
	if (dest == 0 && src == 0)
		return (dest);
	while (n > 0)
	{
		pdest[i] = psrc[i]; 
		i++;
		n--;
	}
	return (dest);
}
