/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcul.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 14:21:54 by avillar           #+#    #+#             */
/*   Updated: 2022/09/07 13:58:55 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/philosopher.h"

// condition acheck die avant de manger = if (((actutime - tmp->lm) + tmp->data->tteat) > tmp->data->ttdie)

int	cee(t_philo *tmp)
{
	int x;
	t_philo	*s;

	if (tmp->data->nte < 0)
	{
		return (0);
	}
	x = 0;
	s = tmp->data->first_philo;
	while (s)
	{
		if (s->et < tmp->data->nte)
			return (0);
		s = s->next_philo;
	}
	pthread_mutex_lock(&tmp->data->lock);
	tmp->data->stop = 1;
	pthread_mutex_unlock(&tmp->data->lock);
	return (1);
}
/*
int	check_for_die(int i, t_philo *philo)
{
	int	actutime;

	actutime = calcul_time(tmp->data->tatstart);
	if (tmp->data->died == 1)
	{
		pthread_mutex_unlock(&tmp->data->lock);
		return (1);
	}
	if ((actutime - ((int)tmp->lm)) + i > tmp->data->ttdie || cee(philo) == 1)
	{
		tmp->data->died = 1;
		tmp->status = 4;
		if ((int)(tmp->data->ttdie - (actutime - tmp->lm)) > 0)
			ft_sleep((tmp->data->ttdie - (actutime - tmp->lm)));
		pthread_mutex_unlock(&tmp->data->lock);
		if (actutime - ((int)tmp->lm + i) > tmp->data->ttdie)
			print(philo, "died");
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&tmp->data->lock);
		return (0);
	}
}*/

int	die_wthink2(int i, t_philo *tmp)
{
	int	actutime;

	pthread_mutex_lock(&tmp->data->lock);
	actutime = calcul_time(tmp->data->tatstart);
	if (tmp->data->died == 1)
	{
		pthread_mutex_unlock(&tmp->data->lock);
		return (1);
	}
	if (((tmp->data->tteat * 2) + tmp->data->ttsleep) + i > tmp->data->ttdie)
	{
		pthread_mutex_unlock(&tmp->data->lock);
		ft_sleep(tmp->data->ttdie - (tmp->data->tteat + tmp->data->ttsleep + 1));
		pthread_mutex_lock(&tmp->data->lock);
		if (tmp->data->died != 1)
		{
			tmp->data->died = 1;
			printf("%llu %d died\n", calcul_time(tmp->data->tatstart), tmp->id);
		}
		tmp->status = 4;
		pthread_mutex_unlock(&tmp->data->lock);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&tmp->data->lock);
		return (0);
	}
}

int	die_wthink(int i, t_philo *tmp)
{
	int	actutime;

	pthread_mutex_lock(&tmp->data->lock);
	actutime = calcul_time(tmp->data->tatstart);
	if (tmp->data->died == 1)
	{
		pthread_mutex_unlock(&tmp->data->lock);
		return (1);
	}
	if ((tmp->data->tteat + tmp->data->ttsleep) + i > tmp->data->ttdie)
	{
		pthread_mutex_unlock(&tmp->data->lock);
		ft_sleep(tmp->data->ttdie - (tmp->data->tteat + tmp->data->ttsleep + 1));
		pthread_mutex_lock(&tmp->data->lock);
		if (tmp->data->died != 1)
		{
			tmp->data->died = 1;
			printf("%llu %d died\n", calcul_time(tmp->data->tatstart), tmp->id);
		}
		tmp->status = 4;
		pthread_mutex_unlock(&tmp->data->lock);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&tmp->data->lock);
		return (0);
	}
}

int	check_for_die2(int i, t_philo *tmp)
{
	int	actutime;

	actutime = calcul_time(tmp->data->tatstart);
	if (tmp->data->died == 1)
	{
		return (1);
	}
	if ((actutime - ((int)tmp->lm)) + i > tmp->data->ttdie)
	{
		if ((int)(tmp->data->ttdie - (actutime - tmp->lm)) > 0)
			ft_sleep((tmp->data->ttdie - (actutime - tmp->lm)));
		pthread_mutex_lock(&tmp->data->lock);
		if (tmp->data->died != 1)
		{
			tmp->data->died = 1;
			printf("%llu %d died\n", calcul_time(tmp->data->tatstart), tmp->id);
		}
		tmp->status = 4;
		pthread_mutex_unlock(&tmp->data->lock);
		return (1);
	}
	else
	{
		return (0);
	}
}

int	check_for_die(int i, t_philo *tmp)
{
	int	actutime;

	actutime = calcul_time(tmp->data->tatstart);
	if (tmp->data->died == 1)
	{
		pthread_mutex_unlock(&tmp->data->lock);
		return (1);
	}
	if ((actutime - ((int)tmp->lm)) + i > tmp->data->ttdie)
	{
		pthread_mutex_unlock(&tmp->data->lock);
		if ((int)(tmp->data->ttdie - (actutime - tmp->lm)) > 0)
			ft_sleep((tmp->data->ttdie - (actutime - tmp->lm)));
		pthread_mutex_lock(&tmp->data->lock);
		if (tmp->data->died != 1)
		{
			tmp->data->died = 1;
			printf("%llu %d died\n", calcul_time(tmp->data->tatstart), tmp->id);
		}
		tmp->status = 4;
		pthread_mutex_unlock(&tmp->data->lock);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&tmp->data->lock);
		return (0);
	}
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