/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   chunk.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clement <clement@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/24 18:24:33 by clement      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/24 19:10:56 by clement     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/malloc.h"

void		*init_chunks_region(t_region *region, size_t size, int type)
{
	t_chunk		*chunk_ptr;
	size_t		chunk_size;
	void		*end_heap;

	region->size = region_size(size, type);
	if (!(region->heap = mmap_page(region->size)))
		return (NULL);
	end_heap = mmap_page(0);
	region->type = type;
	chunk_ptr = (t_chunk *)region->heap;
	chunk_size = (type == TINY) ? TINY_BYTE_MAX : SMALL_BYTE_MAX;
	while ((void *)chunk_ptr + chunk_size < end_heap)
	{
		chunk_ptr->size = chunk_size;
		chunk_ptr->next = (void *)chunk_ptr + chunk_size;
		chunk_ptr = (t_chunk *)chunk_ptr->next;
	}
	chunk_ptr->size = chunk_size;
	chunk_ptr->next = NULL;
	return ((void *)region);
}

t_chunk		*find_free_chunk(t_region *region, size_t size)
{
	t_chunk		*chunk;

	chunk = (t_chunk *)region->heap;
	while (chunk)
	{
		if (IS_FREE(chunk->size) && chunk->size >= size)
		{
			chunk->region = (void *)region;
			return (chunk);
		}
		chunk = (t_chunk *)chunk->next;
	}
	return (NULL);
}

void		*resize_chunk(t_chunk *chunk, size_t size)
{
	t_chunk		*ptr;
	t_chunk		*tmp;

	ptr = chunk;
	while ((ptr->size / 2) >= size)
	{
		tmp = ((t_chunk*)((void*)chunk + (chunk->size / 2)));
		tmp->size = (ptr->size / 2);
		ptr->size = (ptr->size / 2);
		tmp->next = ptr->next;
		ptr->next = tmp;
	}
	ptr->size += 1;
	return (ptr);
}
