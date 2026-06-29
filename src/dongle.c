/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseghrou <mseghrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 11:52:54 by mseghrou          #+#    #+#             */
/*   Updated: 2026/06/29 22:19:09 by mseghrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	is_my_turn(t_coder *c, t_dongle *d)
{
	if (d->queue.size == 0)
		return (1);
	return (d->queue.data[0].coder_id == c->id);
}

static int	is_already_waiting(t_dongle *d, int id)
{
	int	i;

	i = 0;
	while (i < d->queue.size)
	{
		if (d->queue.data[i].coder_id == id)
			return (1);
		i++;
	}
	return (0);
}

void	register_waiter(t_coder *c)
{
	t_waiter	w;

	w.coder_id = c->id;
	w.value = c->wait_value;
	w.tie_id = c->id;
	pthread_mutex_lock(&c->left_dongle->mutex);
	if (!is_already_waiting(c->left_dongle, c->id))
		heap_push(&c->left_dongle->queue, w);
	pthread_mutex_unlock(&c->left_dongle->mutex);
	if (c->left_dongle != c->right_dongle)
	{
		pthread_mutex_lock(&c->right_dongle->mutex);
		if (!is_already_waiting(c->right_dongle, c->id))
			heap_push(&c->right_dongle->queue, w);
		pthread_mutex_unlock(&c->right_dongle->mutex);
	}
}

int	try_take_dongle(t_coder *c, t_dongle *d)
{
	t_waiter	waiter;

	pthread_mutex_lock(&d->mutex);
	if (!d->is_taken && get_time() >= d->release_time && is_my_turn(c, d))
	{
		d->is_taken = 1;
		remove_waiter(d, c->id);
		pthread_mutex_unlock(&d->mutex);
		return (1);
	}
	if (!is_already_waiting(d, c->id))
	{
		waiter.coder_id = c->id;
		waiter.value = c->wait_value;
		waiter.tie_id = c->id;
		heap_push(&d->queue, waiter);
	}
	pthread_mutex_unlock(&d->mutex);
	return (0);
}

void	release_dongle(t_simulation *sim, t_dongle *d)
{
	pthread_mutex_lock(&d->mutex);
	d->is_taken = 0;
	d->release_time = get_time() + sim->args.dongle_cooldown;
	pthread_mutex_unlock(&d->mutex);
}
