/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 19:43:34 by mbesan            #+#    #+#             */
/*   Updated: 2022/04/11 11:57:24 by mbesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	nomnom(t_data *data, int num)
{
	int	a;

	if (data->e_num == -1)
		return (0);
	a = 0;
	while (a < data->num)
	{
		pthread_mutex_lock(&data->phs[a].dth_mutex);
		if (data->phs[a].status != EATING_COMPLETE)
		{
			pthread_mutex_unlock(&data->phs[a].dth_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->phs[a++].dth_mutex);
	}
	if (a == data->num)
	{
		notification(&data->phs[num], EATING_COMPLETE);
		//printf("nn\n");
		return (1);
	}
	return (0);
}

static int	death_cascade(t_data *data, int num)
{
	int	a;

	pthread_mutex_lock(&data->phs[num].lm_mutex);
	if (my_get_time() - data->last_meal[num] >= data->d_time)
	{
		pthread_mutex_lock(&data->phs[num].dth_mutex);
		notification(&data->phs[num], DEAD);
		a = 0;
		while (a < data->num)
		{
			if (a != num)
				pthread_mutex_lock(&data->phs[a].dth_mutex);
			a++;
		}
		//printf("dc\n");
		return (1);
	}
	pthread_mutex_unlock(&data->phs[num].lm_mutex);
	return (0);
}

static void	*checker(void *data)
{
	t_data	*tata;
	int		a;

	tata = data;
	while (1)
	{
		a = 0;
		while (a < tata->num)
		{
			if (death_cascade(tata, a) || nomnom(tata, a))
			{
				//pthread_mutex_unlock(&tata->stop);
				//printf("NOOO\n");
				return ((void *)0);
			}
			a++;
		}
		my_usleep(5);
	}
	return ((void *)0);
}

static void	*philo(void *phil)
{
	t_ph	*phr;

	phr = phil;
	if (phr->num % 2 == 0 && phr->data->status == INIT && phr->sum > 1)
		my_usleep(1);
	while (1)
	{
		if (got_forks(phr) && phr->status != EATING_COMPLETE)
		{
			pthread_mutex_unlock(&phr->dth_mutex);
			eating(phr);
			my_usleep((phr->e_time));
			put_forks(phr);
			notification(phr, SLEEPING);
			my_usleep(phr->s_time);
			notification(phr, THINKING);
		}
		else
		{
			pthread_mutex_unlock(&phr->dth_mutex);
			return ((void *)0);
		}
	}
}

void	start(t_data *data)
{
	int			a;
	int			num;
	pthread_t	monitor;

	a = 0;
	while (a < data->num)
	{
		data->phs[a].start = my_get_time();
		data->phs[a].last_meal = data->phs[a].start;
		data->last_meal[a] = data->phs[a].start;
		a++;
	}
	while (a--)
		pthread_create(&data->phs[a].thr, NULL, &philo, (void *)
			&data->phs[a]);
	num = data->num;
	while (a < num)
		pthread_detach(data->phs[a++].thr);
	pthread_create(&monitor, NULL, &checker, (void *)data);
	pthread_join(monitor, NULL);
}
