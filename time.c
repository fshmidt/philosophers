/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 23:34:15 by mbesan            #+#    #+#             */
/*   Updated: 2022/03/05 18:51:44 by mbesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*int	not_dead(t_ph *phr)
{
	pthread_mutex_lock(&phr->lm_mutex);
	if (my_get_time() - phr->last_meal >= phr->d_time)
	{
		pthread_mutex_unlock(&phr->lm_mutex);
		return (0);
	}
	pthread_mutex_unlock(&phr->lm_mutex);
	return (1);
}*/

long long my_get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((long long int)(t.tv_usec / 1000 + t.tv_sec * 1000));
}
