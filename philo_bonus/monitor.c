/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 19:43:34 by mbesan            #+#    #+#             */
/*   Updated: 2022/04/19 20:54:05 by mbesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	nomnom(t_ph *ph)
{
	sem_wait(ph->dth_sem);
	if (ph->data->e_num == -1)
	{
		sem_post(ph->dth_sem);
		return ;
	}
	if (ph->status == EATING_COMPLETE)
		sem_post(ph->data->nomnom[ph->num]);
	sem_post(ph->dth_sem);
	return ;
}

static int	death_check(t_ph *ph)
{
	sem_wait(ph->lm_sem);
	if (my_get_time() - ph->last_meal >= ph->d_time)
	{
		notification(ph, DEAD);
		return (1);
	}
	sem_post(ph->lm_sem);
	return (0);
}

static void	*checker(void *phr)
{
	t_ph	*ph;

	ph = phr;
	while (1)
	{
		if (death_check(ph))
		{
			sem_post(ph->data->death);
			usleep(100);
			return ((void *)0);
		}
		nomnom(ph);
		my_usleep(4);
	}
}

void	monitor(t_ph *phr)
{
	pthread_t	monitor;

	pthread_create(&monitor, NULL, &checker, (void *)phr);
	pthread_detach(monitor);
}
