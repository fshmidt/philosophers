/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/22 19:09:48 by mbesan            #+#    #+#             */
/*   Updated: 2022/02/28 15:49:11 by mbesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	destroy_other(t_data *data)
{
	int	a;

	a = 0;
	pthread_mutex_lock(&data->death);
	/*if (data->phs)
	{
		while (a < data->num)
		{
			pthread_mutex_destroy(&data->phs[a++].stdout);
		}
	}*/
	pthread_mutex_unlock(&data->death);

	pthread_mutex_destroy(&data->stdout);
	pthread_mutex_destroy(&data->death);
	return (1);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (s != NULL)
	{
		while (s[i])
			i++;
	}
	return (i);
}

long long	ft_atoi(const char *str)
{
	int						i;
	int						minus;
	unsigned long long int	tni;

	i = 0;
	minus = 1;
	tni = 0;
	while (((str[i] <= 13) && (str[i] >= 9)) || ((str[i] == ' ')))
		i++;
	if ((str[i] == '+') || (str[i] == '-'))
	{
		if (str[i++] == '-')
			minus = minus * (-1);
	}
	while ((str[i] >= 48) && (str[i] <= 57))
		tni = (tni * 10) + str[i++] - 48;
	if (tni > 2147483647 && minus > 0)
		return (-1);
	else if (tni > 2147483648 && minus < 0)
		return (0);
	return (tni * minus);
}

int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

void	ft_putnbr(long long n)
{
	if (n / 10)
		ft_putnbr(n / 10);
	write(1, &("0123456789"[n % 10]), 1);
}
