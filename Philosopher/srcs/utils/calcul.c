/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:21:54 by avillar           #+#    #+#             */
/*   Updated: 2022/09/06 13:42:48 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosopher.h"

// condition acheck die avant de manger = if (((actutime - philo->lm) + philo->data->tteat) > philo->data->ttdie)

int	cee(t_philo *tmp)
{
	int x;
	t_philo	*s;

	if (tmp->data->nte < 0)
		return (0);
	x = 0;
	s = tmp->data->first_philo;
	while (s)
	{
		if (s->et < tmp->data->nte)
			return (0);
		s = s->next_philo;
	}
	tmp->data->stop = 1;
	return (1);
}

int	check_for_die(int i, t_philo *philo)
{
	int	actutime;

	actutime = calcul_time(philo->data->tatstart);
	if (philo->data->died == 1)
	{
		pthread_mutex_unlock(&philo->data->lock);
		return (1);
	}
	if ((actutime - (int)philo->lm) + i > philo->data->ttdie)
	{
		philo->data->died = 1;
		philo->status = 4;
		if ((int)(philo->data->ttdie - (actutime - philo->lm)) > 0)
			ft_sleep((int)(philo->data->ttdie - i));
		pthread_mutex_unlock(&philo->data->lock);
		print(philo, "died");
		return (1);
	}
	else
		pthread_mutex_unlock(&philo->data->lock);
	return (0);
}

int	ft_sleep(int i)
{
	i = i * 1000;
	while (i >= 100000)
	{
		usleep(100000);
		i -= 100000;
	}
	if (i <= 100000)
		usleep(i);
	return (0);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

unsigned long long int	calcul_time(struct timeval atstart)
{
	struct	timeval	present;

	gettimeofday(&present, NULL);
	return (((present.tv_sec - atstart.tv_sec) *1000000 + (present.tv_usec - atstart.tv_usec)) / 1000);
}