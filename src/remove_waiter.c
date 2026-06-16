/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_waiter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Meryem <Meryem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/15 18:22:44 by mseghrou          #+#    #+#             */
/*   Updated: 2026/06/16 08:24:02 by Meryem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	remove_waiter(t_dongle *d, int id)
{
	int	i;

	i = 0;
	while (i < d->queue.size)
	{
		if (d->queue.data[i].coder_id == id)
		{
			d->queue.data[i] = d->queue.data[d->queue.size - 1];
			d->queue.size--;
			if (i < d->queue.size)
			{
				bubble_up(&d->queue, i);
				bubble_down(&d->queue, i);
			}
			return ;
		}
		i++;
	}
}
