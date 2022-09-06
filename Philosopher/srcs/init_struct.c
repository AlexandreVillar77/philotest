/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/30 10:32:38 by avillar           #+#    #+#             */
/*   Updated: 2022/09/06 12:58:31 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

t_data	*init_structd(int argc , char **argv)
{
	t_data	*data;

	data = malloc(sizeof(t_data) * 1);
	if (!data)
		exit (EXIT_FAILURE);
	data->first_philo = NULL;
	data->n_philo = ft_atoi(argv[1]);
	data->ttdie = ft_atoi(argv[2]);
	data->tteat = ft_atoi(argv[3]);
	data->ttsleep = ft_atoi(argv[4]);
	data->stop = 0;
	if (argc == 6)
		data->nte = ft_atoi(argv[5]);
	else
		data->nte = -1;
	data->died = 0;
	data->order = 2;
	pthread_mutex_init(&data->lock, NULL);
	return (data);
}

t_philo	*make_philo(t_data *data)
{
	t_philo		*philo;
	static int	id;

	philo = malloc(sizeof(t_philo) * 1);
	if (!philo)
		exit (EXIT_FAILURE);
	id++;
	philo->id = id;
	philo->status = 5;
	philo->next_philo = NULL;
	philo->data = data;
	philo->doing = 0;
	philo->lm = 0;
	philo->nte = data->nte;
	philo->et = 0;
	pthread_mutex_init(&philo->l_fork, NULL);
	return (philo);
}

void	makefork(t_philo *tmp)
{
	int	i;

	i = 0;
	while (i < tmp->data->n_philo - 1)
	{
		tmp->next_philo->r_fork = &tmp->l_fork;
		tmp = tmp->next_philo;
		i++;
	}
	tmp->data->first_philo->r_fork = &tmp->l_fork;
}

t_philo	*create_all_philo(int n, t_data *data)
{
	t_philo	*first;
	t_philo	*actual;

	first = make_philo(data);
	actual = first;
	while (n > 1)
	{
		actual->next_philo = make_philo(data);
		actual = actual->next_philo;
		n--;
	}
	return (first);
}