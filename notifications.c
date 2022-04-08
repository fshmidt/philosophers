/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notifications.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 21:46:18 by mbesan            #+#    #+#             */
/*   Updated: 2022/04/08 08:29:04 by mbesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static char	*msg(int flag)
{
	char	*a;

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
	pthread_mutex_lock(&phr->data->stdt);
	ft_putnbr(my_get_time() - phr->start);
	write(1, " ", 1);
	if (flag != EATING_COMPLETE)
		ft_putnbr(phr->num + 1);
	else
	{
		write(1, msg(flag), ft_strlen(msg(flag)));
		return ;
	}
	write(1, msg(flag), ft_strlen(msg(flag)));
	if (flag != DEAD && flag != EATING_COMPLETE)
		pthread_mutex_unlock(&phr->data->stdt);
}
