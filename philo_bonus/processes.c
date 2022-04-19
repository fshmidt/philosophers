/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   processes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 01:03:06 by mbesan            #+#    #+#             */
/*   Updated: 2022/04/19 10:58:06 by mbesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	eating(t_ph *phr)
{
	sem_wait(phr->lm_sem);
	phr->last_meal = my_get_time();
	sem_post(phr->lm_sem);
	notification(phr, EATING);
	sem_wait(phr->dth_sem);
	phr->e_num += 1;
	if (phr->e_num == phr->e_limit && phr->e_limit != -1)
		phr->status = EATING_COMPLETE;
	sem_post(phr->dth_sem);
}

static void	put_forks(t_ph *phr)
{
	sem_post(phr->data->forks);
	sem_post(phr->data->forks);
}

static int	got_forks(t_ph *phr)
{
	if (phr->sum == 1)
	{
		sem_wait(phr->data->forks);
		notification(phr, FORK_TAKEN);
		sem_wait(phr->dth_sem);
		return (ONE_FORK);
	}
	sem_wait(phr->data->forks);
	notification(phr, FORK_TAKEN);
	sem_wait(phr->data->forks);
	notification(phr, FORK_TAKEN);
	return (BOTH_FORKS);
}

static void	*philo(t_ph	*phr)
{
	monitor(phr);
	if (phr->num % 2 == 0 && phr->data->status == INIT && phr->sum > 1)
		my_usleep(1);
	while (1)
	{
		if (got_forks(phr))
		{
			eating(phr);
			my_usleep((phr->e_time));
			put_forks(phr);
			notification(phr, SLEEPING);
			my_usleep(phr->s_time);
			notification(phr, THINKING);
		}
		else
			return ((void *)0);
	}
}

void	processes(t_data *data)
{
	int	a;

	a = 0;
	while (a < data->num)
	{
		data->phs[a].start = my_get_time();
		data->phs[a].last_meal = data->phs[a].start;
		a++;
	}
	while (a--)
	{
		data->phs[a].pid = fork();
		if (data->phs[a].pid < 0)
			ft_error(data, PROCESS_ERROR, "Can't create a new process\n");
		else if (data->phs[a].pid == 0)
		{
			philo(&data->phs[a]);
			exit(0);
		}
	}
}
