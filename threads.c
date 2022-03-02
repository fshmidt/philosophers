/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 19:43:34 by mbesan            #+#    #+#             */
/*   Updated: 2022/03/02 22:34:32 by mbesan           ###   ########.fr       */
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

static void	*philo(void *phil)
{
	t_ph *phr;

	//printf("?\n");
	phr = phil;
	//printf("s-time = %lld\n", phr->data->s_time);
	//printf("s-time = %lld\n", phr->data->s_time);
	printf("s-time = %lld\n", phr->data->s_time);
	printf("s-time = %lld\n", phr->data->s_time);
	printf("s-time = %lld\n", phr->data->s_time);
	printf("da\n");
	printf("s-time = %lld\n", phr->data->s_time);
	printf("s-time = %lld\n", phr->data->s_time);
	/*if (phr->num % 2 == 0 && phr->status == INIT && phr->data->num > 1)
	{
		phr->status = THINKING;
		notification(phr, THINKING);
		usleep(12000);
	}*/
	printf("s-time = %lld\n", phr->data->s_time);
	printf("ds = %d \n", phr->data->status);
	while (phr->data->status != DEAD)
	{
		phr->status = WAITING;
		printf("s-time = %lld\n", phr->data->s_time);

		ft_putnbr(phr->data->s_time * 1000);
		write(1, "=1time\n",7);
		if (got_forks(phr))
		//ft_putnbr(phr->data->s_time * 1000);
		//write(1, "=2time\n",7);
			eating(phr);
		ft_putnbr(phr->data->s_time * 1000);
		write(1, "=3time\n",7);
		put_forks(phr);
		ft_putnbr(phr->data->s_time * 1000);
		write(1, "=4time\n",7);
		phr->status = SLEEPING;
		notification(phr, SLEEPING);
		ft_putnbr(phr->data->s_time * 1000);
		write(1, "=5time\n",7);
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
		//printf("a\n");
		pthread_create(&data->phs[a].thr, NULL, &philo, (void *)
		&data->phs[a]);
		//printf("b\n");
		pthread_detach(data->phs[a].thr);
		a++;
	}
}
