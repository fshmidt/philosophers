/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:16:16 by mbesan            #+#    #+#             */
/*   Updated: 2022/03/02 02:28:06 by mbesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_ms(t_data *data)
{
	int	a;

	a = 0;
	printf("a = %d\n", a);
	if (pthread_mutex_init(&(data->stdout), NULL) || pthread_mutex_init
		(&(data->death), NULL))
	{
		destroy_other(data);
		ft_error(NO_MEMORY, "Not enough memory\n");
	}
	data->forks = (mutex *)malloc(sizeof(mutex) * data->num);
	if (data->forks == NULL)
	{
		destroy_other(data);
		ft_error(NO_MEMORY, "Not enough memory\n");
	}
	//printf("gghere\n");
	while (a < data->num)
	{
		printf("a = %d\n", a);
		if (pthread_mutex_init(&(data->forks[a++]), NULL))
		{
			destroy_other(data);
			ft_error(NO_MEMORY, "Not enough memory\n");
		}
	}
	//printf("gghere\n");
}

static void	init_philo(t_data *data)
{
	int	a;

	data->phs = (t_ph *)malloc(sizeof(t_ph) * data->num);
	if (data->phs == NULL)
	{
		destroy_other(data);
		ft_error(NO_MEMORY, "Not enough memory\n");
	}
	a = 0;
	//printf("here\n");
	while (a < data->num)
	{
		data->phs[a].num = a;
		//printf("here\n");
		data->phs[a].status = INIT;
		//printf("here\n");
		data->phs[a].last_meal = 0;
		//printf("here\n");
		data->phs[a].r_fork = a;
		//printf("here\n");
		data->phs[a].l_fork = (a + 1) % data->num;
		//printf("here\n");
		data->phs[a].e_num = 0;
		//printf("here\n");
		data->phs[a++].data = data;
		//pthread_mutex_init(&data->phs[a].stdout, NULL);
	}
	//printf("%lli\n", data->phs[1].data->s_time);
}

void init_data(int argc, char **argv, t_data *data, int num)
{
	data->num = num;
	data->d_time = ft_atoi(argv[2]);
	data->e_time = ft_atoi(argv[3]);
	data->s_time = ft_atoi(argv[4]);
	if (argv[5])
		data->e_num = ft_atoi(argv[5]);
	else
		data->e_num = -1;
	data->status = INIT;
	init_philo(data);
	/*printf("lol\n");
	printf("%lli\n", data->phs[1].data->s_time);
	ft_putnbr(data->phs[1].data->s_time * 1000);
	printf("lol\n");
	write(1, "=stime\n",7);*/
	init_ms(data);
}