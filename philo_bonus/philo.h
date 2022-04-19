/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 20:20:54 by mbesan            #+#    #+#             */
/*   Updated: 2022/04/19 10:52:38 by mbesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <sys/types.h>
# include <signal.h>
# include <stdio.h>

# define NO_DATA NULL
# define L_M "/lm"
# define DTH "/dt"

enum	e_ex
{
	OK,
	WRONG_ARG_N,
	SHT_ARGS,
	NO_MEMORY,
	PROCESS_ERROR,
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
	NOMNOM,
};

enum	e_sem
{
	LAST_MEAL,
	DEATH,
};

typedef pthread_mutex_t	t_mutex;

struct					s_data;

typedef struct s_ph
{
	int				num;
	int				status;
	long long		e_time;
	long long		d_time;
	long long		s_time;
	long long		last_meal;
	long long		start;
	sem_t			*lm_sem;
	sem_t			*dth_sem;
	int				e_num;
	int				e_limit;
	int				sum;
	pid_t			pid;
	struct s_data	*data;
}					t_ph;

typedef struct s_data
{
	int				num;
	int				status;
	long long		e_time;
	long long		d_time;
	long long		s_time;
	int				e_num;
	sem_t			*forks;
	sem_t			*stdt;
	sem_t			*death;
	sem_t			**nomnom;
	t_ph			*phs;
}					t_data;

void				ft_error(t_data *data, int error_num, char *error_msg);
void				init_data(char **argv, t_data *data, int num);
void				notification(t_ph *phr, int flag);
void				my_usleep(long long int time);
void				ft_putnbr(long long int num);
void				destroy_other(t_data *data);
void				monitor(t_ph *phr);
void				processes(t_data *data);

long long int		ft_atoi(const char *str);
long long int		my_get_time(void);
size_t				ft_strlen(const char *s);
int					ft_isdigit(int c);
int					not_dead(t_ph *phr);

#endif