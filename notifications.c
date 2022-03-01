/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notifications.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 21:46:18 by mbesan            #+#    #+#             */
/*   Updated: 2022/03/01 16:02:56 by mbesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	*msg(int flag)
{
	char *a;

	if (flag == FORK_TAKEN)
		a = " has taken a fork\n";
	else if (flag == EATING)
		a = " is eating\n";
	else if (flag == SLEEPING)
		a = " is sleeping\n";
	else if (flag == THINKING)
		a = " is thinking\n";
	else if (flag == DEAD)
		a = " died\n";
	else if (flag == EATING_COMPLETE)
		a = "all philosophers have eaten required amount of times\n";
	else
		a = " died\n";
	return (a);
}

void	notification(t_ph *phr, int flag)
{
	//usleep(150000);
	pthread_mutex_lock(&phr->data->stdout);
	if (phr->data->status == DEAD)
	{
		pthread_mutex_lock(&phr->data->death);
		phr->data->status = STOP;
	}
	if (phr->data->status != STOP)
	{
		ft_putnbr(my_get_time() - phr->last_meal);
		write(1, " ", 1);
		if (flag != EATING_COMPLETE)
			ft_putnbr(phr->num + 1);
		//write(1, "/", 1);
		write(1, msg(flag), ft_strlen(msg(flag)));
	}
	pthread_mutex_unlock(&phr->data->stdout);
	//usleep(150000);
	//pthread_mutex_unlock(&phr->data->death);
}