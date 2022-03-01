/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 01:03:06 by mbesan            #+#    #+#             */
/*   Updated: 2022/03/01 20:00:49 by mbesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eating(t_ph *phr)
{
	long long	a;

	phr->last_meal = my_get_time();
	phr->status = EATING;
	notification(phr, EATING);
	//while (my_get_time() < phr->data->e_time + phr->last_meal)
		usleep(100000);
	ft_putnbr(phr->data->s_time);
	write(1, "estime\n",7);
	phr->e_num += 1;
}

void	put_forks(t_ph *phr)
{
	if (phr->num + 1 != phr->data->num)
	{
		pthread_mutex_unlock(&phr->data->forks[phr->r_fork]);
		//write(1, "put r\n", 6);
		pthread_mutex_unlock(&phr->data->forks[phr->l_fork]);
		//write(1, "put l\n", 6);
	}
	else
	{
		pthread_mutex_unlock(&phr->data->forks[phr->l_fork]);
		//write(1, "put l\n", 6);
		pthread_mutex_unlock(&phr->data->forks[phr->r_fork]);
		//write(1, "put r\n", 6);
	}
}

void	get_forks(t_ph *phr)
{
	if (phr->num + 1 != phr->data->num)
	{
		//write(1, "rfork=", 6);
		//ft_putnbr(phr->r_fork);
		//write(1, "\n", 1);
		pthread_mutex_lock(&phr->data->forks[phr->r_fork]);
		notification(phr, FORK_TAKEN);
		//write(1, "lfork=", 6);
		//ft_putnbr(phr->l_fork);
		//write(1, "\n", 1);
		pthread_mutex_lock(&phr->data->forks[phr->l_fork]);
		notification(phr, FORK_TAKEN);
	}
	else
	{
		//write(1, "lfork=", 6);
		//ft_putnbr(phr->l_fork);
		//write(1, "\n", 1);
		pthread_mutex_lock(&phr->data->forks[phr->l_fork]);
		notification(phr, FORK_TAKEN);
		//write(1, "rfork=", 6);
		//ft_putnbr(phr->r_fork);
		//write(1, "\n", 1);
		pthread_mutex_lock(&phr->data->forks[phr->r_fork]);
		///write(1, "here3\n", 6);
		notification(phr, FORK_TAKEN);
	}
}