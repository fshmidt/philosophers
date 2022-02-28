/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 01:03:06 by mbesan            #+#    #+#             */
/*   Updated: 2022/02/28 21:38:01 by mbesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_ph *phr)
{
	long long	a;

	phr->last_meal = my_get_time();
	phr->status = EATING;
	notification(phr, EATING);
	usleep(phr->data->e_time * 1000);
	phr->e_num += 1;
}

void	put_forks(t_ph *phr)
{
	if (phr->num + 1 != phr->data->num)
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

void	get_forks(t_ph *phr)
{
	if (phr->num + 1 != phr->data->num)
	{
		pthread_mutex_lock(&phr->data->forks[phr->r_fork]);
		notification(phr, FORK_TAKEN);
		pthread_mutex_lock(&phr->data->forks[phr->l_fork]);
		notification(phr, FORK_TAKEN);
	}
	else
	{
		//write(1, "here1\n", 6);
		pthread_mutex_lock(&phr->data->forks[phr->l_fork]);
		notification(phr, FORK_TAKEN);
		//write(1, "here2\n", 6);
		pthread_mutex_lock(&phr->data->forks[phr->r_fork]);
		//write(1, "here3\n", 6);
		notification(phr, FORK_TAKEN);
	}
}