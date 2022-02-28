/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 19:43:34 by mbesan            #+#    #+#             */
/*   Updated: 2022/02/28 21:10:39 by mbesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	*viewer(void *data)
{
	t_data *tata;
	int	a;

	tata = data;
	while (tata->status != STOP)
	{
		a = 0;
		while (a < tata->num &&  tata->phs[a].status != INIT)
		{
			/*pthread_mutex_lock(&tata->stdout);
			ft_putnbr(a);
			write(1, "=a\n", 3);
			ft_putnbr(my_get_time());
			write(1, "=t\n", 3);
			pthread_mutex_unlock(&tata->stdout);*/
			if (my_get_time() - tata->phs[a].last_meal >= tata->d_time)
			{
				write(1, "done\n", 5);//exit(0);
				notification(&tata->phs[a], DEAD);
				tata->phs[a].status = DEAD;
				tata->status = DEAD;
				usleep(1000000);
				//if (destroy_other(tata))
				return ((void *)0);
			}
			a++;
			//usleep(10000);
		}

	}
	return ((void*)0);
}

static void	*philo(void *philo)
{
	t_ph *phr;

	phr = philo;
	phr->last_meal = my_get_time();
	if (phr->num % 2 == 0 && phr->status == INIT)
	{
		phr->status = THINKING;
		//notification(phr, THINKING);
		usleep(12000);
	}
	while (phr->data->status != DEAD)
	{
		phr->status = WAITING;
		get_forks(phr);
		eating(phr);
		put_forks(phr);
		phr->status = SLEEPING;
		notification(phr, SLEEPING);
		usleep(phr->data->s_time * 1000);
		phr->status = THINKING;
		notification(phr, THINKING);
	}
	if (phr->data->status == DEAD)
		write(1, "dead\n", 1);
	return ((void*)0);
}

void	start(t_data *data)
{
	int			a;
	pthread_t	monitor;

	a = 0;
	//pthread_create(&monitor, NULL, &viewer, (void *)data);
	//pthread_detach(monitor);
	while (a < data->num)
	{
		pthread_create(&data->phs[a].thr, NULL, &philo, (void *)
		&data->phs[a]);
		pthread_detach(data->phs[a].thr);
		a++;
	}
}
