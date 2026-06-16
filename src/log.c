/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mseghrou <mseghrou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/09 11:53:12 by mseghrou          #+#    #+#             */
/*   Updated: 2026/06/15 17:02:00 by mseghrou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"
#include <sys/time.h>

long	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	log_action(t_simulation *sim, int id, char *msg)
{
	long	time;

	pthread_mutex_lock(&sim->log_mutex);
	time = get_time() - sim->start_time;
	printf("%ld %d %s\n", time, id, msg);
	pthread_mutex_unlock(&sim->log_mutex);
}
