/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_pop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseghrou <mseghrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 11:52:58 by mseghrou          #+#    #+#             */
/*   Updated: 2026/06/16 12:51:43 by mseghrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	waiter_less(t_waiter *a, t_waiter *b)
{
	if (a->value != b->value)
		return (a->value < b->value);
	return (a->tie_id < b->tie_id);
}

void	bubble_down(t_heap *h, int i)
{
	int	left;
	int	right;
	int	smallest;

	while (1)
	{
		left = 2 * i + 1;
		right = 2 * i + 2;
		smallest = i;
		if (left < h->size && waiter_less(&h->data[left], &h->data[smallest]))
			smallest = left;
		if (right < h->size && waiter_less(&h->data[right], &h->data[smallest]))
			smallest = right;
		if (smallest == i)
			break ;
		swap(&h->data[i], &h->data[smallest]);
		i = smallest;
	}
}

t_waiter	heap_pop(t_heap *h)
{
	t_waiter	top;

	if (h->size <= 0)
		return ((t_waiter){0});
	top = h->data[0];
	h->data[0] = h->data[h->size - 1];
	h->size--;
	if (h->size > 0)
		bubble_down(h, 0);
	return (top);
}
