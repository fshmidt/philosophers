/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 20:20:54 by mbesan            #+#    #+#             */
/*   Updated: 2022/04/07 17:13:34 by mbesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
//# include <limits.h>

# define NO_DATA NULL

enum	e_ex
{
	OK,
	WRONG_ARG_N,
	SHT_ARGS,
	NO_MEMORY,
	MUTEX_INIT_ERR,
};

enum	e_forks
{
	ONE_FORK,
	BOTH_FORKS,
};

enum	e_status
{
	INIT,
	ALIVE,
	FORK_TAKEN,
	EATING,
	SLEEPING,
	THINKING,
	EATING_COMPLETE,
	DEAD,
};

typedef pthread_mutex_t	t_mutex;

struct					s_data;

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
	t_mutex			lm_mutex;
	t_mutex			dth_mutex;
	int				e_num;
	int				e_limit;
	int				sum;
	pthread_t		thr;
	struct s_data	*data;
}					t_ph;

typedef struct s_data
{
	int				num;
	int				status;
	long long		e_time;
	long long		d_time;
	long long		s_time;
	long long		*last_meal;
	int				e_num;
	t_mutex			*forks;
	t_mutex			stdt;
	t_ph			*phs;
}					t_data;

void				ft_error(t_data *data, int error_num, char *error_msg);
void				init_data(char **argv, t_data *data, int num);
void				notification(t_ph *phr, int flag);
void				my_usleep(long long int time);
void				ft_putnbr(long long int num);
void				destroy_other(t_data *data);
void				start(t_data *data);
void				put_forks(t_ph *phr);
void				eating(t_ph *phr);

long long int		ft_atoi(const char *str);
long long int		my_get_time(void);
size_t				ft_strlen(const char *s);
int					got_forks(t_ph *phr);
int					ft_isdigit(int c);
int					not_dead(t_ph *phr);

#endif