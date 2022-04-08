/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 20:17:26 by mbesan            #+#    #+#             */
/*   Updated: 2022/03/11 03:03:48 by mbesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_error(t_data *data, int error_num, char *error_msg)
{
	write(1, error_msg, ft_strlen(error_msg));
	usleep(1000000);
	if (data != NULL)
		destroy_other(data);
	exit(error_num);
}

static int	not_validated(int argc, char **argv)
{
	int	a;
	int	b;

	a = 1;
	while (argc - a)
	{
		b = 0;
		while (argv[a][b])
		{
			if (!ft_isdigit(argv[a][b++]))
				return (1);
		}
		a++;
	}
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[2]) < 0 || ft_atoi(argv[3])
		< 0 || ft_atoi(argv[4]) < 0 || ft_atoi(argv[1]) >= 200)
		return (1);
	if (argv[5] && ft_atoi(argv[5]) <= 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	data = NULL;
	if (argc < 5 || argc > 6)
		ft_error(NO_DATA, WRONG_ARG_N, "Wrong arguments number.\n");
	if (not_validated(argc, argv))
		ft_error(NO_DATA, SHT_ARGS, "Wrong arguments.\n");
	data = (t_data *)malloc(sizeof(t_data));
	if (data == NULL)
		ft_error(NO_DATA, NO_MEMORY, "Not enough memory\n");
	init_data(argv, data, ft_atoi(argv[1]));
	start(data);
	//free(data);
	return (0);
}
