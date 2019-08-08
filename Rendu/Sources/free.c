/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/08 14:49:31 by clement      #+#   ##    ##    #+#       */
/*   Updated: 2019/08/08 16:28:23 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

int		is_preallocation(int type)
{
	t_region	*region;
	int			count;

	if (type == LARGE)
		return (0);
	count = 0;
	region = g_region;
	while (region->next)
	{
		if (region->type == type)
			count++;
		region = region->next;
		if (region->type == type)
			count++;
	}
	if (count > 1)
		return (0);
	return (1);
}

int		free_region(t_region *region)
{
	if (region->used || !(region->type))
		return (0);
	if (!(is_preallocation(region->type)))
	{
		munmap(region->heap, region->size);
		region->type = 0;
		region->size = 0;
		region->used = 0;
		region->heap = NULL;
	}
	else
		ft_memset(region->heap, 0, region->size);
	return (1);
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
		if (region->start == 1)
			munmap(region, REGION_MMAP_SIZE);
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
	if (free_region(region))
		free_metadata();
}
