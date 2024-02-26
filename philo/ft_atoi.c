/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 09:58:05 by mozennou          #+#    #+#             */
/*   Updated: 2024/01/19 12:01:22 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	check(char *s)
{
	int	pm;

	pm = 0;
	if (!*s)
		return (-1);
	if (*s == '+')
		s++;
	if (!*s)
		return (-1);
	while (*s && ((*s >= '0' && *s <= '9')))
		s++;
	if (*s)
		return (-1);
	return (0);
}

int	ft_atoi(char *s, int *num)
{
	int				i;
	int				digits;
	unsigned long	res;

	digits = 0;
	if (check(s))
		return (-1);
	i = 0;
	res = 0;
	if (*s == '+')
		s++;
	while (s[i] == '0')
		i++;
	while (s[i] && s[i] >= '0' && s[i] <= '9')
	{
		res = (res * 10) + (s[i++] - '0');
		digits++;
	}
	if (res > INT_MAX || digits >= 11)
		return (-1);
	return (*num = (int)res, 0);
}
