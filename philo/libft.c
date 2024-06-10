/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:56:04 by njackson          #+#    #+#             */
/*   Updated: 2024/06/10 15:23:05 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_uint	ft_atou_strict(const char *str, int *err)
{
	t_uint	out;
	t_uint	chkof;

	if (*str < '0' || *str > '9')
		return ((*err = 1), 0);
	out = 0;
	while (*str >= '0' && *str <= '9')
	{
		chkof = out;
		out = (out * 10) + (*(str++) - 48);
		if (out / 10 != chkof)
			return ((*err = 1), 0);
	}
	if (*str)
		return ((*err = 1), 0);
	return (out);
}

int	check_mutex_int(int *addr, t_mutex *lock)
{
	int	out;

	pthread_mutex_lock(lock);
	out = *addr;
	pthread_mutex_unlock(lock);
	return (out);
}

void	add_mutex_int(int *addr, t_mutex *lock, int add)
{
	pthread_mutex_lock(lock);
	*addr += add;
	pthread_mutex_unlock(lock);
}

int	time_dif(t_tv start, t_tv *time)
{
	t_tv	tmp;
	int		out;

	if (!time)
		time = &tmp;
	gettimeofday(time, NULL);
	out = (time->tv_sec - start.tv_sec) * 1000000;
	out += time->tv_usec - start.tv_usec;
	return (out);
}

void	print_action(t_philo *philo, t_tv *time, char *action)
{
	int	ms;

	pthread_mutex_lock(&philo->dat->print_lock);
	ms = time_dif(philo->dat->start_time, time) / 1000;
	printf(C_GRAY"%8d"C_NC"    %-4d %s\n", ms, philo->num, action);
	pthread_mutex_unlock(&philo->dat->print_lock);
}
