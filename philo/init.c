/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:16:16 by mbesan            #+#    #+#             */
/*   Updated: 2022/04/16 20:32:51 by mbesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	init_ms(t_data *data)
{
	int	a;

	a = 0;
	if (pthread_mutex_init(&data->stdt, NULL))
		ft_error(data, MUTEX_INIT_ERR, "Mutex init error\n");
	data->forks = (t_mutex *)malloc(sizeof(*(data->forks)) * data->num);
	if (data->forks == NULL)
		ft_error(data, NO_MEMORY, "Not enough memory\n");
	while (a < data->num)
	{
		if (pthread_mutex_init(&(data->forks[a++]), NULL))
			ft_error(data, MUTEX_INIT_ERR, "Mutex init error\n");
	}
	while (a--)
	{
		if (pthread_mutex_init(&(data->phs[a].lm_mutex), NULL))
			ft_error(data, MUTEX_INIT_ERR, "Mutex init error\n");
	}
	a = 0;
	while (a < data->num)
	{
		if (pthread_mutex_init(&(data->phs[a++].dth_mutex), NULL))
			ft_error(data, MUTEX_INIT_ERR, "Mutex init error\n");
	}
}

static void	init_philo(t_data *data)
{
	int	a;

	a = 0;
	while (a < data->num)
	{
		data->phs[a].num = a;
		data->phs[a].sum = data->num;
		data->phs[a].status = ALIVE;
		data->phs[a].start = 0;
		data->phs[a].last_meal = 0;
		data->last_meal[a] = 0;
		data->phs[a].s_time = data->s_time;
		data->phs[a].e_time = data->e_time;
		data->phs[a].d_time = data->d_time;
		data->phs[a].r_fork = a;
		data->phs[a].l_fork = (a + 1) % data->num;
		data->phs[a].e_num = 0;
		data->phs[a].e_limit = data->e_num;
		data->phs[a++].data = data;
	}
}

void	init_data(char **argv, t_data *data, int num)
{
	data->num = num;
	data->d_time = ft_atoi(argv[2]);
	data->e_time = ft_atoi(argv[3]);
	data->s_time = ft_atoi(argv[4]);
	if (argv[5])
		data->e_num = ft_atoi(argv[5]);
	else
		data->e_num = -1;
	data->phs = NULL;
	data->last_meal = NULL;
	data->forks = NULL;
	data->phs = (t_ph *)malloc(sizeof(t_ph) * data->num);
	if (data->phs == NULL)
		ft_error(data, NO_MEMORY, "Not enough memory\n");
	data->last_meal = (long long *)malloc(sizeof(long long) * data->num);
	if (data->last_meal == NULL)
		ft_error(data, NO_MEMORY, "Not enough memory\n");
	data->status = INIT;
	init_philo(data);
	init_ms(data);
}
