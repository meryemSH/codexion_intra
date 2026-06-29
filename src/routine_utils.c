/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseghrou <mseghrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 11:53:29 by mseghrou          #+#    #+#             */
/*   Updated: 2026/06/29 22:19:21 by mseghrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

static t_dongle	*first_dongle(t_coder *c)
{
	if (c->left_dongle < c->right_dongle)
		return (c->left_dongle);
	return (c->right_dongle);
}

static t_dongle	*second_dongle(t_coder *c)
{
	if (c->left_dongle < c->right_dongle)
		return (c->right_dongle);
	return (c->left_dongle);
}

static void	abort_take_dongle(t_coder *c, t_dongle *d)
{
	t_waiter	waiter;

	pthread_mutex_lock(&d->mutex);
	d->is_taken = 0;
	d->release_time = 0;
	waiter.coder_id = c->id;
	waiter.value = c->wait_value;
	waiter.tie_id = c->id;
	heap_push(&d->queue, waiter);
	pthread_mutex_unlock(&d->mutex);
}

int	take_dongles(t_coder *c)
{
	t_dongle	*first;
	t_dongle	*second;

	if (c->left_dongle == c->right_dongle)
	{
		if (try_take_dongle(c, c->left_dongle))
			log_action(c->sim, c->id, "has taken a dongle");
		return (0);
	}
	first = first_dongle(c);
	second = second_dongle(c);
	if (!try_take_dongle(c, first))
		return (0);
	if (!try_take_dongle(c, second))
	{
		abort_take_dongle(c, first);
		return (0);
	}
	log_action(c->sim, c->id, "has taken a dongle");
	log_action(c->sim, c->id, "has taken a dongle");
	pthread_mutex_lock(&c->time_mutex);
	c->last_compile_time = get_time();
	pthread_mutex_unlock(&c->time_mutex);
	return (1);
}

int	coder_finished(t_coder *c)
{
	t_simulation	*sim;
	int				count;

	sim = c->sim;
	if (sim->args.number_of_compiles_required <= 0)
		return (0);
	pthread_mutex_lock(&c->compile_mutex);
	count = c->compile_count;
	pthread_mutex_unlock(&c->compile_mutex);
	if (count >= sim->args.number_of_compiles_required)
		return (1);
	return (0);
}

void	smart_sleep(long time, t_simulation *sim)
{
	long	start;

	start = get_time();
	while (get_time() - start < time && get_isrunning(sim) == true)
		usleep(500);
}
