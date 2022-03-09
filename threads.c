/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 19:43:34 by mbesan            #+#    #+#             */
/*   Updated: 2022/03/09 03:32:57 by mbesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	nomnom(t_data *data, int num)
{
	int	a;

	if (data->e_num == -1)
		return (0);
	pthread_mutex_lock(&data->phs[num].lm_mutex);
	if (data->phs[num].e_num >= data->e_num)
		data->phs[num].status = EATING_COMPLETE;
	pthread_mutex_unlock(&data->phs[num].lm_mutex);
	a = 0;
	while (a < data->num)
	{
		pthread_mutex_lock(&data->phs[a].lm_mutex);
		if (data->phs[a].status != EATING_COMPLETE)
		{
			pthread_mutex_unlock(&data->phs[a].lm_mutex);
			return (0);
		}
		pthread_mutex_unlock(&data->phs[a++].lm_mutex);
	}
	if (a == data->num)
		notification(&data->phs[num], EATING_COMPLETE);
	return (1);
}

static int	death_cascade(t_data *data, int num)
{
	int	a;

	if (my_get_time() - data->last_meal[num] >= data->d_time)
	{
		pthread_mutex_unlock(&data->phs[num].lm_mutex);
		notification(&data->phs[num], DEAD);
		a = 0;
		while (a < data->num)
		{
			pthread_mutex_lock(&data->phs[a].lm_mutex);
			data->phs[a].status = DEAD;
			pthread_mutex_unlock(&data->phs[a++].lm_mutex);
		}
		return (1);
	}
	pthread_mutex_unlock(&data->phs[num].lm_mutex);
	return (0);
}

static void	*viewer(void *data)
{
	t_data *tata;
	int		a;
	int		num;

	tata = data;
	num = tata->num;
	while (1)
	{
		a = 0;
		while (a < num)
		{
			pthread_mutex_lock(&tata->phs[a].lm_mutex);
			if (death_cascade(tata, a) || nomnom(tata, a))
			{
				put_forks(&tata->phs[a]);
				usleep(100);
				//destroy_other(tata);
				exit(0);
			}
			pthread_mutex_unlock(&tata->phs[a].lm_mutex);
			a++;
		}
		usleep(1000);
	}
	return ((void*)0);
}

static void	*philo(void *phil)
{
	t_ph *phr;

	phr = phil;
	if (phr->num % 2 == 0 && phr->data->status == INIT && phr->sum > 1)
		usleep(1500);
	while (1)
	{
		if (got_forks(phr) && phr->status != DEAD)
		{
			pthread_mutex_unlock(&phr->lm_mutex);
			eating(phr);
			usleep((phr->e_time) * 1000);
			put_forks(phr);
			notification(phr, SLEEPING);
			usleep(phr->s_time * 1000);
			notification(phr, THINKING);
			usleep(800);
		}
		else
		{
			pthread_mutex_unlock(&phr->lm_mutex);
			usleep((phr->d_time + 20)* 1000);
			return ((void*)DEAD);
		}
	}
}

void	start(t_data *data)
{
	int			a;
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
	pthread_create(&monitor, NULL, &viewer, (void *)data);
	while (a++ < data->num)
		pthread_join(data->phs[a].thr, NULL);
	pthread_join(monitor, NULL);
}
