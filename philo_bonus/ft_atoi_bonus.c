/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mozennou <mozennou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 09:58:05 by mozennou          #+#    #+#             */
/*   Updated: 2024/01/19 12:01:02 by mozennou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

static int	func(int n, int *neg)
{
	int				l;
	unsigned int	k;

	l = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		(*neg) = 1;
		n = -n;
		l++;
	}
	k = n;
	while (k >= 1)
	{
		l++;
		k = k / 10;
	}
	return (l);
}

char	*ft_itoa(int n)
{
	char			*res;
	int				neg;
	unsigned int	k;
	int				ln;

	neg = 0;
	ln = func(n, &neg);
	if (neg == 1)
		n *= -1;
	k = n;
	res = (char *)malloc(ln + 1);
	if (res == NULL)
		return (NULL);
	if (neg)
		res[0] = '-';
	res[ln] = '\0';
	if (k == 0)
		res[0] = '0';
	while (k != 0)
	{
		res[ln-- - 1] = k % 10 + '0';
		k = k / 10;
	}
	return (res);
}
