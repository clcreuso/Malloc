/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clement <clement@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/08 14:49:31 by clement      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/27 16:54:14 by clement     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/malloc.h"

void	free_region(t_region *region)
{
	if (!(region->used) && (region->type))
	{
		munmap(region->heap, region->size);
		region->type = 0;
		region->size = 0;
		region->used = 0;
		region->heap = NULL;
	}
}

void	free_metadata(void)
{
	t_region *region;
	t_region *tmp;

	region = g_region;
	while (region->next)
	{
		if (region->type)
			return ;
		region = region->next;
	}
	if (region->type)
		return ;
	while (region)
	{
		tmp = region->prev;
		if (region->start)
			munmap(region, 4096);
		region = tmp;
	}
	g_region = NULL;
}

void	free(void *ptr)
{
	t_region	*region;
	t_chunk		*chunk;

	if (!(ptr) || !(check_chunk_exist(ptr)))
		return ;
	chunk = (t_chunk *)(ptr - sizeof(struct s_chunk));
	region = (t_region *)chunk->region;
	if (!(IS_FREE(chunk->size)))
	{
		chunk->size -= 1;
		region->used -= chunk->size;
	}
	free_region(region);
	free_metadata();
}
