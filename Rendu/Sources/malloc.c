/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   malloc.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clement <clement@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/08 14:16:09 by clement      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/15 17:40:40 by clement     ###    #+. /#+    ###.fr     */
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

void	*mmap_region(size_t size)
{
	static void 	*region_next = NULL;
	void			*region_address;
	
	region_address = mmap(region_next, size, PROT_READ | PROT_WRITE,
					   	  MAP_ANON | MAP_PRIVATE, -1, 0);

	if (region_address != MAP_FAILED)
		region_next = region_address + size;
	
	return (region_address);
}

t_chunk	*find_chunk(t_chunk *start, size_t size, int type)
{
	static t_chunk	*threshold = NULL;
	t_chunk			*tmp;
	
	tmp = start;
	
	if (!threshold)
		threshold = start + REGION_SIZE(type);

	while(tmp->next)
		tmp = tmp->next;
		
	if ((unsigned int)(tmp + size) > (unsigned int)threshold)
	{
		if ((tmp->next = mmap_region(REGION_SIZE(type))) == MAP_FAILED)
			return (NULL);
		threshold = threshold + REGION_SIZE(type);
		tmp = tmp->next;
	}

	return (tmp);
}

void	*test_malloc(size_t size, int type)
{
	static t_chunk	*tiny_heap = NULL;
	static t_chunk	*small_heap = NULL;
	t_chunk			*last_chunk;
	
	if (type == TINY && !tiny_heap)
		if ((tiny_heap = mmap_region(REGION_SIZE(type))) == MAP_FAILED)
			return (NULL);
	if (type == SMALL && !small_heap)
		if ((small_heap = mmap_region(REGION_SIZE(type))) == MAP_FAILED)
			return (NULL);
	if (type == SMALL && !(last_chunk = find_chunk(small_heap, size, type)))
		return (NULL);
	if (type == TINY && !(last_chunk = find_chunk(tiny_heap, size, type)))
		return (NULL);
	else
	{
		last_chunk->alloc_size = size;
		last_chunk->chunk_size = rounded_allocation(size);
		last_chunk->next = (void *)last_chunk + last_chunk->chunk_size;
	}
	
	return (last_chunk + sizeof(struct s_chunk));
}

void	*ft_malloc(size_t size)
{
	if (TINY_SIZE(size) || SMALL_SIZE(size))
		return test_malloc(size, TINY);
	// if (MALLOC_LARGE(size))
	// 	return large_malloc(size);
		
	return (NULL);
}
