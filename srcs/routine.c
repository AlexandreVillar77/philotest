/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 11:38:09 by avillar           #+#    #+#             */
/*   Updated: 2022/09/06 16:06:14 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	wait_other(t_philo *tmp)
{
	static	int	wait;

	pthread_mutex_lock(&tmp->data->lock);
	if (wait == 1)
	{
		pthread_mutex_unlock(&tmp->data->lock);
	}
	else
	{
		ft_sleep(100);
		wait++;
		gettimeofday(&tmp->data->tatstart, NULL);
		pthread_mutex_unlock(&tmp->data->lock);
	}
}

int		change_order(int i)
{
	if (i == 2)
		return (1);
	else
		return (2);
}

int	check_for_nte(t_philo *tmp)
{
	if (tmp->nte == 0)
		return (1);
	return (0);
}

void	*routine(void *philo)
{
	t_philo			*tmp;

	tmp = (t_philo*)philo;
	wait_other(tmp);
	while (tmp->data->died == 0 && tmp->data->stop == 0)
	{
		if (check_for_die(0, tmp) == 1)
			return (0);
		if (tmp->id % tmp->data->order == 0 && tmp->data->died == 0
			&& tmp->data->stop == 0)
		{
			tmp->data->order = go_eat(tmp);
			if (tmp->data->died == 0 && tmp->data->stop == 0)
				go_sleep(tmp);
		}
		if (tmp->status != 0 && tmp->data->died == 0 && tmp->data->stop == 0)
			is_thinking(tmp);
	}
	return (0);
}