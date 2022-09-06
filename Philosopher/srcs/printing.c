/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 09:40:11 by avillar           #+#    #+#             */
/*   Updated: 2022/09/06 15:56:17 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	print(t_philo *tmp, char *str)
{
	pthread_mutex_lock(&tmp->data->lock);
	if ((tmp->data->died == 1 || tmp->data->stop == 1) && tmp->status != 4)
	{
		pthread_mutex_unlock(&tmp->data->lock);
		return ;
	}
	printf("%llu %d %s\n", calcul_time(tmp->data->tatstart), tmp->id, str);
	pthread_mutex_unlock(&tmp->data->lock);
}

//check avec 3 philo aque le troisieme meur bien si il prend une fourchette et que son temps expire

void	print_fork(t_philo *tmp)
{
	pthread_mutex_lock(tmp->r_fork);
	if (tmp->data->stop == 1)
		return ;
	tmp->status = 3;
	print(tmp, "has taken a fork");
	pthread_mutex_lock(&tmp->l_fork);
	print(tmp, "has taken a fork");
}

void	go_sleep(t_philo *tmp)
{
	print(tmp, "is sleeping");
	tmp->status = 2;
	if (check_for_die(tmp->data->ttsleep, tmp) == 1)
		return ;
	ft_sleep(tmp->data->ttsleep);
}

void	is_thinking(t_philo *tmp)
{
	print(tmp, "is thinking");
	tmp->status = 0;
}

void	print_eat(t_philo *tmp, char *str)
{
	if (tmp->lm > 0)
		printf("%llu ", tmp->lm);
	else
		printf("%llu ", calcul_time(tmp->data->tatstart));
	printf("%d %s\n", tmp->id, str);
}

int		go_eat(t_philo *tmp)
{
	print_fork(tmp);
	tmp->status = 1;
	pthread_mutex_lock(&tmp->data->lock);
	if (tmp->data->died == 1 || tmp->data->stop == 1)
	{
		pthread_mutex_unlock(&tmp->l_fork);
		pthread_mutex_unlock(tmp->r_fork);
		pthread_mutex_unlock(&tmp->data->lock);
		return (1);
	}
	tmp->lm = calcul_time(tmp->data->tatstart);
	print_eat(tmp, "is eating");
	if (check_for_die(tmp->data->tteat, tmp) == 1)
	{
		pthread_mutex_unlock(&tmp->l_fork);
		pthread_mutex_unlock(tmp->r_fork);
		return (1);
	}
	ft_sleep(tmp->data->tteat);
	tmp->et++;
	pthread_mutex_lock(&tmp->data->lock);
	cee(tmp);
	pthread_mutex_unlock(&tmp->data->lock);
	pthread_mutex_unlock(&tmp->l_fork);
	pthread_mutex_unlock(tmp->r_fork);
	if (tmp->id % 2 == 0)
		return (1);
	else
		return (2);
}