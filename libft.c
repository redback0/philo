/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: njackson <njackson@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/30 11:56:04 by njackson          #+#    #+#             */
/*   Updated: 2024/05/30 12:04:24 by njackson         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi_strict(const char *str, int *err)
{
	int	out;
	int	chkof;
	int	sign;

	sign = 1;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	if (*str < '0' || *str > '9')
		return ((*err = 1), 0);
	out = 0;
	while (*str >= '0' && *str <= '9')
	{
		chkof = out;
		out = (out * 10) + (*(str++) - 48);
		if (out / 10 != chkof && (sign == 1 || !(out < 0 && out - 1 > 0)))
			return ((*err = 1), 0);
	}
	if (*str)
		return ((*err = 1), 0);
	return (sign * out);
}
