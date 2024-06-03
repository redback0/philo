/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:29:24 by njackson          #+#    #+#             */
/*   Updated: 2024/06/03 13:26:22 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int ac, char *av[])
{
	t_philo	dat;

	(void)av;
	(void)ac;
	init_threads(&dat);
//	if (ac < 5 || ac > 7)
//		return (ft_log(0, USAGE), 0);
//	set_philo_dat(ac, av, &dat);
}

int	set_philo_dat(int ac, char **av, t_philo *dat)
{
	int err;

	err = 0;
	dat->num_philo = ft_atoi_strict(av[1], &err);
	dat->die_time = ft_atoi_strict(av[2], &err);
	dat->eat_time = ft_atoi_strict(av[3], &err);
	dat->sleep_time = ft_atoi_strict(av[4], &err);
	if (ac == 6)
		dat->each_eat = ft_atoi_strict(av[5], &err);
	return (err);
}

void	init_threads(t_philo *dat)
{
	pthread_t	thread;
	int	i;

	i = 0;
	while (i < 5)
	{
		pthread_create(&thread, NULL, (void *)(void *)thread_func, dat);
		pthread_detach(thread);
		i++;
	}
	usleep(1000);
}

void	thread_func(t_philo *dat)
{
	(void)dat;
	printf("Hello world!\n");
}
