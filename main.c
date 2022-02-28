/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbesan <mbesan@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 20:17:26 by mbesan            #+#    #+#             */
/*   Updated: 2022/02/28 01:03:23 by mbesan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
void	ft_error(int error_num, char *error_msg)
{
	write(1, error_msg, ft_strlen(error_msg));
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
	if (ft_atoi(argv[1]) < 2 || ft_atoi(argv[2]) < 0 || ft_atoi(argv[3])
		< 0 || ft_atoi(argv[4]) < 0)
		return (1);
	if (argv[5] && ft_atoi(argv[5]) <= 0)
		return (1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (argc < 5 || argc > 6)
		ft_error(WRONG_ARG_N, "Wrong arguments number.\n");
	if (not_validated(argc, argv))
		ft_error(SHT_ARGS, "Wrong arguments.\n");
	init_data(argc, argv, &data, ft_atoi(argv[1]));
	start(&data);
	return (0);
}