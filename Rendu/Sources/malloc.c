/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   malloc.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clement <clement@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/08 14:16:09 by clement      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/17 15:49:56 by clement     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/malloc.h"
#include <stdio.h>
#include <sys/mman.h>

unsigned int	rounded_allocation(unsigned int size_allocation)
{
	unsigned int	rounded_allocation;
	
	rounded_allocation = 32;
	
	size_allocation += sizeof(struct s_chunk);
	
	while (rounded_allocation < size_allocation)
		rounded_allocation *= 2;

	return (rounded_allocation);
}

size_t			adjust_allocation(int type)
{
	static size_t	align[2] = {2, 2};
	size_t			size;

	size = REGION_SIZE(type) * align[type];
	
	align[type] = align[type] << 1;
	
	return (size);
}

void			*mmap_region(void **threshold, int type)
{
	static void 	*region_next = NULL;
	void			*region_address;
	size_t			size;

	size = adjust_allocation(type);

	region_address = mmap(region_next, size, PROT_READ | PROT_WRITE,
					   	  MAP_ANON | MAP_PRIVATE, -1, 0);

	if (region_address != MAP_FAILED)
	{
		region_next = region_address + size;
		*(threshold) += size;
	}
	
	return (region_address);
}

t_chunk				*find_chunk(t_chunk **start, size_t size, int type)
{
	static void	*threshold[2] = {NULL, NULL};
	t_chunk		*last;
	t_chunk		*tmp;
	
	if (!*(start))
		if ((*(start) = mmap_region(&threshold[type], type)) == MAP_FAILED)
			return (NULL);

	tmp = *(start);
	
	while (tmp)
		if (IS_FREE(tmp->chunk_size) && tmp->chunk_size == size)
			return (tmp);
		else
		{
			last = tmp;
			tmp = tmp->next;
		}
	
	if (((void*)last + size) >= threshold[type])
	{
		if ((last->next = mmap_region(&threshold[type], type)) == MAP_FAILED)
			return (NULL);
		else
			return (last->next);
	}
	
	last->next = (t_chunk*)((void*)last + size);
	
	return (last->next);
}

void	*test_malloc(t_chunk **region_heap, size_t size, int type)
{
	t_chunk			*last_chunk;
	size_t 			chunk_size;

	chunk_size = rounded_allocation(size);
	if (!(last_chunk = find_chunk(region_heap, chunk_size, type)))
		return (NULL);
	else
	{
		last_chunk->alloc_size = size;
		last_chunk->chunk_size = chunk_size + 1;
	}
	
	return ((void*)last_chunk + sizeof(struct s_chunk));
}

void	*ft_malloc(size_t size)
{
	static t_chunk	*tiny_heap = NULL;
	static t_chunk	*small_heap = NULL;
	
	if (TINY_SIZE(size))
		return test_malloc(&tiny_heap, size, TINY);
	if (SMALL_SIZE(size))
		return test_malloc(&small_heap, size, SMALL);
	// if (MALLOC_LARGE(size))
	// 	return large_malloc(size);
		
	return (NULL);
}
