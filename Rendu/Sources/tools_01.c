/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_01.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/24 15:17:45 by clement      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/03 11:36:20 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

int			region_type(size_t size)
{
	if (size >= TINY_BYTE_MIN && size <= TINY_BYTE_MAX)
		return (TINY);
	if (size >= SMALL_BYTE_MIN && size <= SMALL_BYTE_MAX)
		return (SMALL);
	if (size >= LARGE_BYTE_MIN)
		return (LARGE);
	return (0);
}

int			region_size(size_t size, int type)
{
	if (type == TINY)
		return (TINY_MMAP_SIZE);
	if (type == SMALL)
		return (SMALL_MMAP_SIZE);
	if (type == LARGE)
		return (size);
	return (0);
}

size_t		round_size(size_t size)
{
	size_t	result;

	result = 64;
	size += sizeof(struct s_chunk);
	while (result < size)
		result *= 2;
	return (result);
}

void		*mmap_page(size_t size)
{
	static void	*region_next = NULL;
	void		*result;

	if (!(size))
		return (region_next);
	result = mmap(0, size, PROT_READ | PROT_WRITE,
							MAP_ANON | MAP_PRIVATE, -1, 0);
	if (result != MAP_FAILED)
		region_next = result + size;
	else
		return (NULL);
	return (result);
}
