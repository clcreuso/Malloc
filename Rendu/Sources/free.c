/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/08 14:49:31 by clement      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/03 11:36:20 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

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

	if (!(ptr))
		return ;
	chunk = (t_chunk *)(ptr - sizeof(struct s_chunk));
	if (!(region = check_chunk_exist((void*)chunk)))
		return ;
	if (!(IS_FREE(chunk->size)))
	{
		chunk->size -= 1;
		region->used -= chunk->size;
	}
	free_region(region);
	free_metadata();
}
