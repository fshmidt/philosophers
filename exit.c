/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 19:17:59 by mbesan            #+#    #+#             */
/*   Updated: 2022/03/09 03:09:23 by mbesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_phs(t_data *data)
{
	int	a;
	
	a = 0;
	while (a < data->num)
		pthread_mutex_unlock(&data->phs[a++].lm_mutex);
	while (a--)
		pthread_mutex_destroy(&data->phs[a].lm_mutex);
	free(data->phs);
}

static void	destroy_forks(t_data *data)
{
	int	a;
	
	a = 0;
	while (a < data->num)
		pthread_mutex_unlock(&data->forks[a++]);
	while (a--)
		pthread_mutex_destroy(&data->forks[a]);
	free(data->forks);
}

void	destroy_other(t_data *data)
{
	int	a;

	a = 0;
	if (data->phs)
		destroy_phs(data);
	if (data->forks)
		destroy_forks(data);
	pthread_mutex_unlock(&data->stdt);
	pthread_mutex_destroy(&data->stdt);
	if (data->last_meal)
		free(data->last_meal);
	free(data);
}