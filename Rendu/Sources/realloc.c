/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   realloc.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clement <clement@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/08 14:10:16 by clement      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/27 16:54:41 by clement     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/malloc.h"

void	*realloc(void *ptr, size_t size)
{
	t_region	*region;
	t_chunk		*chunk;
	void		*new_ptr;

	chunk = (t_chunk *)(ptr - sizeof(struct s_chunk));
	region = (t_region *)chunk->region;
	if (chunk->size >= (size + sizeof(struct s_chunk)))
		return (ptr);
	if ((new_ptr = malloc(size)))
		ft_strncpy(new_ptr, ptr, (chunk->size - sizeof(struct s_chunk)));
	free(ptr);
	return (new_ptr);
}
