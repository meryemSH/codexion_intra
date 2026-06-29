/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseghrou <mseghrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 12:05:15 by mseghrou          #+#    #+#             */
/*   Updated: 2026/06/29 22:18:51 by mseghrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	get_isrunning(t_simulation *sim)
{
	int	value;

	pthread_mutex_lock(&sim->lock);
	value = sim->is_running;
	pthread_mutex_unlock(&sim->lock);
	return (value);
}

int	check_take_dongles(t_coder *coder)
{
	if (!take_dongles(coder))
	{
		usleep(500);
		return (0);
	}
	return (1);
}

int	do_compile_cycle(t_coder *coder, t_simulation *sim)
{
	log_action(sim, coder->id, "is compiling");
	smart_sleep((long)sim->args.time_to_compile, sim);
	pthread_mutex_lock(&coder->compile_mutex);
	coder->compile_count++;
	pthread_mutex_unlock(&coder->compile_mutex);
	release_dongle(sim, coder->left_dongle);
	if (coder->left_dongle != coder->right_dongle)
		release_dongle(sim, coder->right_dongle);
	if (!get_isrunning(sim))
		return (0);
	log_action(sim, coder->id, "is debugging");
	smart_sleep((long)sim->args.time_to_debug, sim);
	if (!get_isrunning(sim))
		return (0);
	log_action(sim, coder->id, "is refactoring");
	smart_sleep((long)sim->args.time_to_refactor, sim);
	return (1);
}

void	join_threads(t_simulation *sim)
{
	int	i;

	i = 0;
	pthread_join(sim->monitor_thread, NULL);
	while (i < sim->args.number_of_coders)
	{
		pthread_join(sim->coders[i].thread, NULL);
		i++;
	}
}
