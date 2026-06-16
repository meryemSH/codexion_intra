/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_push.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseghrou <mseghrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 11:53:01 by mseghrou          #+#    #+#             */
/*   Updated: 2026/06/16 12:51:37 by mseghrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

void	swap(t_waiter *a, t_waiter *b)
{
	t_waiter	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	heap_init(t_heap *h, int capacity)
{
	h->size = 0;
	h->capacity = 0;
	h->data = malloc(sizeof(t_waiter) * capacity);
	if (!h->data)
		return ;
	h->capacity = capacity;
}

void	bubble_up(t_heap *h, int i)
{
	int	parent;

	while (i > 0)
	{
		parent = (i - 1) / 2;
		if (!waiter_less(&h->data[i], &h->data[parent]))
			break ;
		swap(&h->data[i], &h->data[parent]);
		i = parent;
	}
}

void	heap_push(t_heap *h, t_waiter w)
{
	if (h->size >= h->capacity)
		return ;
	h->data[h->size] = w;
	bubble_up(h, h->size);
	h->size++;
}
