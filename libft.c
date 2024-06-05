/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:56:04 by njackson          #+#    #+#             */
/*   Updated: 2024/06/05 13:16:03 by njackson         ###   ########.fr       */
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

int	ft_min(int a, int b)
{
	return ((a < b) * a + (a >= b) * b);
}

int	time_dif(t_tv start)
{
	t_tv	time;
	int		out;

	gettimeofday(&time, NULL);
	out = (time.tv_sec - start.tv_sec) * 1000000;
	out += (time.tv_usec - start.tv_usec);
	return (out);
}

void	print_action(t_philo *philo, char *action)
{
	int		ms;

	ms = time_dif(philo->dat->start_time) / 1000;
	printf("%8d %d %s\n", ms, philo->num, action);
}
