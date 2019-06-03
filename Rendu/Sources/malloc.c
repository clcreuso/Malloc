/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   malloc.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/08 14:16:09 by clement      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/03 11:36:20 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

void		*large_malloc(t_region *region, size_t size)
{
	t_chunk	*chunk;

	region->type = LARGE;
	region->used = size;
	region->size = size;
	region->heap = mmap_page(size);
	chunk = (t_chunk *)region->heap;
	chunk->size = size + 1;
	chunk->next = NULL;
	return ((void*)chunk + sizeof(struct s_chunk));
}

void		*smart_malloc(size_t size, int type)
{
	t_region	*region_ptr;
	t_chunk		*chunk_ptr;
	void		*result;

	region_ptr = NULL;
	while ((region_ptr = find_metadata_region(region_ptr, type)))
	{
		if (!(region_ptr->type))
		{
			if (type == LARGE)
				return (large_malloc(region_ptr, size));
			if (!(init_chunks_region(region_ptr, size, type)))
				return (NULL);
		}
		if ((chunk_ptr = find_free_chunk(region_ptr, size)))
			if ((result = resize_chunk(chunk_ptr, size)))
			{
				region_ptr->used += size;
				return (result + sizeof(struct s_chunk));
			}
	}
	return (NULL);
}

void		*malloc(size_t size)
{
	int		type;

	size = round_size(size);
	type = region_type(size);
	init_metadata_region();
	if (type == TINY)
		return (smart_malloc(size, TINY));
	if (type == SMALL)
		return (smart_malloc(size, SMALL));
	if (type == LARGE)
		return (smart_malloc(size, LARGE));
	return (NULL);
}
