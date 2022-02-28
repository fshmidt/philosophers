/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:16:16 by mbesan            #+#    #+#             */
/*   Updated: 2022/02/28 20:45:34 by mbesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_ms(t_data *data)
{
	int	a;

	a = 0;
	pthread_mutex_init(&data->stdout, NULL);
	pthread_mutex_init(&data->death, NULL);
	data->forks = (mutex *)malloc(sizeof(mutex) * data->num);
	if (data->forks == NULL)
	{
		destroy_other(data);
		ft_error(NO_MEMORY, "Not enough memory\n");
	}
	while (a < data->num)
		pthread_mutex_init(&data->forks[a++], NULL);
}

static void	init_philo(t_data *data)
{
	int	a;

	a = 0;
	while (a < data->num)
	{
		data->phs[a].num = a;
		data->phs[a].status = INIT;
		data->phs[a].last_meal = 0;
		data->phs[a].r_fork = a;
		data->phs[a].l_fork = (a + 1) % data->num;
		data->phs[a].e_num = 0;
		data->phs[a].data = data;
		//pthread_mutex_init(&data->phs[a].stdout, NULL);
		a++;
	}
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
	init_ms(data);
}