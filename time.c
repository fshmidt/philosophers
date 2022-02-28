/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 23:34:15 by mbesan            #+#    #+#             */
/*   Updated: 2022/02/28 17:45:51 by mbesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long my_get_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((long long int)(t.tv_usec / 1000 + t.tv_sec * 1000));
}
