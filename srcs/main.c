/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/29 11:40:56 by avillar           #+#    #+#             */
/*   Updated: 2022/09/07 12:46:36 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philosopher.h"

void	print_data(t_data *data)
{
	printf("ttdie = %d\n", data->ttdie);
	printf("tteat = %d\n", data->tteat);
	printf("ttttsleep = %d\n", data->ttsleep);
	printf("n_philo = %d\n", data->n_philo);
	if (data->nte)
		printf("nte = %d\n", data->nte);
}

void	print_philo(t_philo	*philo)
{
	t_philo	*tmp;

	tmp = philo;
	while (tmp)
	{
		printf("id = %d\n", tmp->id);
		tmp = tmp->next_philo;
	}
}

int	philo_loop(t_data *data)
{
	int		i;
	t_philo	*tmp;

	tmp = data->first_philo;
	i = 0;
	while (i < data->n_philo)
	{
		pthread_create(&tmp->thread, NULL, &routine, tmp);
		tmp = tmp->next_philo;
		i++;
	}
	i = -1;
	tmp = data->first_philo;
	while (++i < data->n_philo)
	{
		pthread_join(tmp->thread, NULL);
		tmp = tmp->next_philo;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;
	if (parsing_glo(argc, argv) == 1)
		return (1);
	data = init_structd(argc, argv);
	data->first_philo = create_all_philo(data->n_philo, data);
	makefork(data->first_philo);
	philo_loop(data);
	free_data(data);
	return (0);
}
