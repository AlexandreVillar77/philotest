/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/02 09:40:11 by avillar           #+#    #+#             */
/*   Updated: 2022/09/07 14:00:23 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	print(t_philo *tmp, char *str)
{
	pthread_mutex_lock(&tmp->data->lock);
	if (tmp->data->died == 1 && tmp->status != 4)
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
	tmp->status = 3;
	print(tmp, "has taken a fork");
	pthread_mutex_lock(&tmp->l_fork);
	print(tmp, "has taken a fork");
}

void	go_sleep(t_philo *tmp)
{
	printf("%llu %d %s\n", calcul_time(tmp->data->tatstart), tmp->id, "is sleeping");
	if (check_for_die(tmp->data->ttsleep, tmp) == 1)
		return ;
	tmp->status = 2;
	ft_sleep(tmp->data->ttsleep);
}

void	is_one(t_philo *tmp)
{

	static int	y;

	pthread_mutex_lock(&tmp->data->lock);
	if (y == 1)
	{
		pthread_mutex_unlock(&tmp->data->lock);
		return ;
	}
	y++;
	if (tmp->data->n_philo == 1)
	{
		tmp->data->died = 1;
		pthread_mutex_unlock(&tmp->data->lock);
		tmp->status = 4;
		print(tmp, "has taken a fork");
		ft_sleep(tmp->data->ttdie);
		print(tmp, "died");
		tmp->status = 0;
		return ;
	}
	pthread_mutex_unlock(&tmp->data->lock);
}

void	is_thinking(t_philo *tmp)
{
	is_one(tmp);
	print(tmp, "is thinking");
	tmp->status = 0;
}

void	print_eat(t_philo *tmp, char *str)
{
	if (tmp->lm > 0)
	{
		printf("%llu %d %s\n", tmp->lm, tmp->id, str);
		return ;
	}
	printf("%llu %d %s\n", calcul_time(tmp->data->tatstart), tmp->id, str);
}

int	unlock_mutex(int mode, t_philo *tmp)
{
	if (mode == 1)
	{
		pthread_mutex_unlock(&tmp->l_fork);
		pthread_mutex_unlock(tmp->r_fork);
		pthread_mutex_unlock(&tmp->data->lock);
	}
	else if (mode == 0)
		pthread_mutex_unlock(&tmp->data->lock);
	else if (mode == 2)
	{
		pthread_mutex_unlock(&tmp->l_fork);
		pthread_mutex_unlock(tmp->r_fork);
	}
	return (1);
}

int		go_eat(t_philo *tmp)
{
	print_fork(tmp);
	tmp->status = 1;
	pthread_mutex_lock(&tmp->data->lock);
	if (tmp->data->died == 1 || tmp->data->stop == 1)
		return (unlock_mutex(1, tmp));
	tmp->lm = calcul_time(tmp->data->tatstart);
	print_eat(tmp, "is eating");
	if (check_for_die(tmp->data->tteat, tmp) == 1)
		return (unlock_mutex(2, tmp));
	ft_sleep(tmp->data->tteat);
	tmp->et++;
	if (tmp->data->nte > 0)
		cee(tmp);
	unlock_mutex(2, tmp);
	pthread_mutex_lock(&tmp->data->lock);
	if (tmp->id % 2 == 0)
		tmp->data->order = 1;
	else
		tmp ->data->order = 2;
	pthread_mutex_unlock(&tmp->data->lock);
	return (0);
}