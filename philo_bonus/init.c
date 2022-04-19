/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 18:16:16 by mbesan            #+#    #+#             */
/*   Updated: 2022/04/19 10:59:00 by mbesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	sem_name(char *name, int flag, int num)
{
	if (flag == LAST_MEAL)
		name[0] = 'l';
	else if (flag == DEATH)
		name[0] = 'd';
	else
		name[0] = 'n';
	name[1] = num / 100 + '0';
	name[2] = num / 10 % 10 + '0';
	name[3] = num % 10 + '0';
	name[4] = '\0';
}

static sem_t	*my_sem_open(int flag, int num, int counter)
{
	sem_t	*semaphore;
	char	name[5];

	sem_name((char *)name, flag, num);
	semaphore = sem_open((const char *)name, O_CREAT, S_IRWXU, counter);
	sem_unlink(name);
	return (semaphore);
}

static void	init_sem(t_data *data)
{
	int	a;

	data->stdt = sem_open("/stdt", O_CREAT, S_IRWXU, 1);
	sem_unlink("/stdt");
	data->forks = sem_open("/forks", O_CREAT, S_IRWXU, data->num);
	sem_unlink("/forks");
	data->death = sem_open("/death", O_CREAT, S_IRWXU, 0);
	sem_unlink("/death");
	a = data->num;
	while (a--)
		data->phs[a].lm_sem = my_sem_open(LAST_MEAL, a, 1);
	a = data->num;
	while (a--)
		data->phs[a].dth_sem = my_sem_open(DEATH, a, 1);
	a = data->num;
	while (a--)
		data->nomnom[a] = my_sem_open(NOMNOM, a, 0);
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
		data->phs[a].s_time = data->s_time;
		data->phs[a].e_time = data->e_time;
		data->phs[a].d_time = data->d_time;
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
	data->nomnom = NULL;
	data->forks = NULL;
	data->phs = (t_ph *)malloc(sizeof(t_ph) * data->num);
	if (data->phs == NULL)
		ft_error(data, NO_MEMORY, "Not enough memory\n");
	data->nomnom = (sem_t **)malloc(sizeof(sem_t *) * data->num);
	if (data->nomnom == NULL)
		ft_error(data, NO_MEMORY, "Not enough memory\n");
	data->status = INIT;
	init_philo(data);
	init_sem(data);
}
