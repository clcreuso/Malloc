/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   region.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/24 15:07:22 by clement      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/03 11:36:20 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

t_region	*find_metadata_region(t_region *region, int type)
{
	t_region	*ptr;

	ptr = (region) ? region->next : g_region;
	while (ptr)
	{
		if (ptr->type == type && ptr->used != ptr->size)
			return (ptr);
		ptr = ptr->next;
	}
	ptr = g_region;
	while (ptr->next)
	{
		if (!(ptr->type))
			return (ptr);
		ptr = ptr->next;
	}
	return (NULL);
}

t_region	*new_metadata_region(void)
{
	t_region	*ptr;
	t_region	*result;
	void		*threshold;

	ptr = (t_region *)mmap_page(REGION_MMAP_SIZE);
	threshold = mmap_page(0);
	result = ptr;
	result->start = 1;
	result->prev = NULL;
	while ((void *)ptr + (sizeof(struct s_region) * 2) < threshold)
	{
		ptr->next = (void *)ptr + sizeof(struct s_region);
		ptr = ptr->next;
		ptr->prev = (void *)ptr - sizeof(struct s_region);
	}
	ptr->next = NULL;
	return (result);
}

void		init_metadata_region(void)
{
	t_region	*region;

	if (!g_region)
		g_region = new_metadata_region();
	else
	{
		region = g_region;
		while (region->next)
		{
			if (!(region->type))
				return ;
			region = region->next;
		}
		region->next = new_metadata_region();
	}
}
