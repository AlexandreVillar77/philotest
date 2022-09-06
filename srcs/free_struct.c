/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_struct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/01 10:04:28 by avillar           #+#    #+#             */
/*   Updated: 2022/09/06 12:51:14 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	destroy(t_data *philo)
{
	int	i;
	t_philo	*tmp;

	i = 0;
	tmp = philo->first_philo;
	while (i < philo->n_philo && tmp)
	{
		pthread_mutex_destroy(&tmp->l_fork);
		tmp = tmp->next_philo;
		i++;
	}
}

void	free_philo(t_data *p, int m)
{
	int	i;
	t_philo	*tmp;

	i = 0;
	destroy(p);
	while (m >= 0)
	{
		i = 0;
		tmp = p->first_philo;
		while (i < m)
		{
			i++;
			tmp = tmp->next_philo;
		}
		free(tmp);
		m--;
	}
}

void	free_data(t_data *data)
{
	free_philo(data, data->n_philo);
	pthread_mutex_destroy(&data->lock);
	free (data);
}