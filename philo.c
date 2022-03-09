/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 01:03:06 by mbesan            #+#    #+#             */
/*   Updated: 2022/03/09 03:13:43 by mbesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_ph *phr)
{
	pthread_mutex_lock(&phr->lm_mutex);
	phr->last_meal = my_get_time();
	phr->data->last_meal[phr->num] = phr->last_meal;
	phr->e_num += 1;
	pthread_mutex_unlock(&phr->lm_mutex);
	notification(phr, EATING);
}

void	put_forks(t_ph *phr)
{
	if (phr->num + 1 != phr->sum)
	{
		pthread_mutex_unlock(&phr->data->forks[phr->r_fork]);
		pthread_mutex_unlock(&phr->data->forks[phr->l_fork]);
	}
	else
	{
		pthread_mutex_unlock(&phr->data->forks[phr->l_fork]);
		pthread_mutex_unlock(&phr->data->forks[phr->r_fork]);
	}
}

int	got_forks(t_ph *phr)
{
	if (phr->sum == 1)
	{
		//printf("p\n");
		pthread_mutex_lock(&phr->data->forks[phr->r_fork]);
		//printf("ph\n");
		notification(phr, FORK_TAKEN);
		pthread_mutex_lock(&phr->lm_mutex);
		return (0);
	}
	if (phr->num + 1 != phr->sum)
	{
		pthread_mutex_lock(&phr->data->forks[phr->r_fork]);
		notification(phr, FORK_TAKEN);
		pthread_mutex_lock(&phr->data->forks[phr->l_fork]);
		notification(phr, FORK_TAKEN);
	}
	else
	{
		pthread_mutex_lock(&phr->data->forks[phr->l_fork]);
		notification(phr, FORK_TAKEN);
		pthread_mutex_lock(&phr->data->forks[phr->r_fork]);
		notification(phr, FORK_TAKEN);
	}
	pthread_mutex_lock(&phr->lm_mutex);
	return (1);
}