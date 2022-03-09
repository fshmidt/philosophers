/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 20:20:54 by mbesan            #+#    #+#             */
/*   Updated: 2022/03/09 03:07:53 by mbesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
#define PHILO_H

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <pthread.h>
#include <limits.h>
#include <stdio.h>//////////////////////////////////////////

//#ifndef NO_DATA
#define NO_DATA NULL
//#endif

enum	e_ex
{
	OK,
	WRONG_ARG_N,
	SHT_ARGS,
	NO_MEMORY,
	MUTEX_INIT_ERR,
};

enum	e_status
{
	INIT,
	ALIVE,
	//WAITING,
	FORK_TAKEN,
	EATING,
	SLEEPING,
	THINKING,
	EATING_COMPLETE,
	DEAD,
	//STOP,
};

typedef pthread_mutex_t mutex;

struct s_data;

typedef struct s_ph
{
	int				num;
	long long		l_fork;
	long long		r_fork;
	int				status;
	long long		e_time;
	long long		d_time;
	long long		s_time;
	long long		last_meal;
	long long		start;
	mutex			lm_mutex;
	//mutex			go;
	int				e_num;
	int				sum;
	pthread_t		thr;
	struct s_data	*data;
}					t_ph;

typedef struct s_data
{
	int			num;
	int			status;
	long long	e_time;
	long long	d_time;
	long long	s_time;
	long long	*last_meal;
	int			e_num;
	mutex		*forks;
	mutex		stdt;
	//mutex		status_mutex;
	t_ph		*phs;
}				t_data;

void		ft_error(t_data *data, int error_num, char *error_msg);
void		start(t_data *data);
void		ft_putnbr(long long int);
int			got_forks(t_ph *phr);
void		put_forks(t_ph *phr);
void		eating(t_ph *phr);
void		destroy_other(t_data *data);
void		notification(t_ph *phr, int flag);
void		init_data(int argc, char **argv, t_data *data, int num);

long long int	my_get_time(void);
size_t			ft_strlen(const char *s);
long long int	ft_atoi(const char *str);
int				ft_isdigit(int c);
int				not_dead(t_ph *phr);


#endif