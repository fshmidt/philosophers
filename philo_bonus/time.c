/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 23:34:15 by mbesan            #+#    #+#             */
/*   Updated: 2022/04/10 18:35:39 by mbesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	my_usleep(long long int time)
{
	long long int	i;

	i = my_get_time();
	while (my_get_time() - i < time)
		usleep(10);
}

long long int	my_get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((long long int)(t.tv_usec / 1000 + t.tv_sec * 1000));
}
