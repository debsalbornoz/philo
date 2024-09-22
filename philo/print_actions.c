/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_actions.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlamark- <dlamark-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:48:19 by codespace         #+#    #+#             */
/*   Updated: 2024/09/22 00:02:56 by dlamark-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	print_actions(long int time, char *action, t_philo *philo)
{
	char	*ft_time;
	char	*str;
	char	*i;
	int		len;

	if (safe_mutex_lock(&philo->monitor->print_status))
	{
		ft_time = ft_itoa(time);
		i = ft_itoa((long int)philo->index);
		len = ft_strlen(ft_time) + ft_strlen(i) + ft_strlen(action) + 5;
		str = malloc(len * sizeof(char));
		str[0] = '\0';
		ft_strlcat(str, ft_time, ft_strlen(ft_time) + 1);
		ft_strlcat(str, " ", ft_strlen(ft_time) + 2);
		ft_strlcat(str, i, ft_strlen(str) + ft_strlen(i) + 1);
		ft_strlcat(str, action, ft_strlen(str) + ft_strlen(action) + 1);
		if (!philo_is_dead(philo))
		{
			ft_putstr_fd(str, 1);
			free(str);
		}
		safe_mutex_unlock(&philo->monitor->print_status);
	}
}

int	get_digits(long int nbr)
{
	unsigned int	counter;

	counter = 1;
	if (nbr < 0)
		nbr = nbr * -1;
	while (nbr > 9)
	{
		nbr = nbr / 10;
		counter++;
	}
	return (counter);
}

char	*ft_itoa(long int n)
{
	char		*str;
	size_t		num_digits;
	long int	num;

	num = n;
	num_digits = get_digits(n);
	if (n < 0)
	{
		num = num * -1;
		num_digits++;
	}
	str = (char *)malloc(sizeof(char) * (num_digits + 1));
	if (str == NULL)
		return (NULL);
	*(str + num_digits) = '\0';
	while (num_digits--)
	{
		*(str + num_digits) = num % 10 + '0';
		num = num / 10;
	}
	if (n < 0)
		*(str + 0) = '-';
	return (str);
}

int	ft_strlcat(char *dst, char *src, int size)
{
	int	i;
	int	j;
	int	dst_len;
	int	src_len;

	i = 0;
	j = 0;
	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size <= dst_len)
		return (size + src_len);
	while (dst[i] != '\0' && i < size - 1)
		i++;
	while (src[j] != '\0' && i < size - 1)
	{
		dst[i] = src[j];
		i++;
		j++;
	}
	dst[i] = '\0';
	return (dst_len + src_len);
}

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}
