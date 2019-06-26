/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   realloc.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clement <clement@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/08 14:10:16 by clement      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/24 20:48:44 by clement     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

void	*realloc(void *ptr, size_t size)
{
	t_region	*region;
	t_chunk		*chunk;
	void		*new_ptr;

	if (!ptr)
		return (malloc(size));
	chunk = (t_chunk *)(ptr - sizeof(struct s_chunk));
	if (!(region = check_chunk_exist((void*)chunk)))
		return (NULL);
	if (chunk->size >= (size + sizeof(struct s_chunk)))
		return (ptr);
	if ((new_ptr = malloc(size)))
		ft_memncpy(new_ptr, ptr, (chunk->size - 1) - sizeof(struct s_chunk));
	free(ptr);
	return (new_ptr);
}
