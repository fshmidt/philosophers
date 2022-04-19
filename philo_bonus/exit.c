/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/06 19:17:59 by mbesan            #+#    #+#             */
/*   Updated: 2022/04/19 10:49:45 by mbesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_other(t_data *data)
{
	if (data->nomnom)
		free(data->nomnom);
	if (data->phs)
		free(data->phs);
	free(data);
}
