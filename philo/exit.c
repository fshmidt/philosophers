/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 19:17:59 by mbesan            #+#    #+#             */
/*   Updated: 2022/04/19 10:54:25 by mbesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	destroy_phs(t_data *data)
{
	int	a;

	a = data->num;
	while (a--)
		pthread_mutex_destroy(&data->phs[a].lm_mutex);
	free(data->phs);
}

static void	destroy_forks(t_data *data)
{
	int	a;

	a = data->num;
	while (a--)
		pthread_mutex_destroy(&data->forks[a]);
}

void	destroy_other(t_data *data)
{
	if (data->phs)
		destroy_phs(data);
	if (data->forks)
		destroy_forks(data);
	if (data->last_meal)
		free(data->last_meal);
	pthread_mutex_destroy(&data->stdt);
	free(data);
}
