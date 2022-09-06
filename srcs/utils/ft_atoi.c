/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 10:38:02 by avillar           #+#    #+#             */
/*   Updated: 2022/08/30 14:54:58 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosopher.h"

int	mallocsize(unsigned int nb, int s, int n)
{
	if (n < 0)
	{
		n = 0;
		s++;
	}
	if (nb < 10)
		return (s + 1);
	return (mallocsize((nb / 10), s += 1, n));
}

int	neg(int n)
{
	unsigned int	neg;

	if (n < 0)
		neg = n * -1;
	else
		neg = n;
	return (neg);
}

char	*ft_itoa(int n)
{
	char			*rtn;
	int				i;
	int				len;
	unsigned int	nb;

	i = 0;
	if (n < 0)
		i++;
	nb = neg(n);
	len = mallocsize(nb, 0, n);
	rtn = malloc(sizeof(char) * len + 1);
	if (!rtn)
		return (0);
	if (i > 0)
		rtn[0] = '-';
	rtn[len] = '\0';
	while (len > i)
	{
		rtn[len - 1] = (nb % 10) + 48;
		nb = nb / 10;
		len--;
	}
	return (rtn);
}

int	ft_atoi(const char *str)
{
	long int	rtn;
	int			nb;

	rtn = 0;
	nb = 1;
	while (*str == ' ' || *str == '\t' || *str == '\n' || *str == '\f'
		|| *str == '\r' || *str == '\v')
		str++;
	if (*str == '-')
		nb = -1;
	if (*str == '-' || *str == '+')
		str++;
	while (*str >= 48 && *str <= 57)
	{
		rtn *= 10;
		rtn += *str - 48;
		str++;
	}
	return (rtn * nb);
}