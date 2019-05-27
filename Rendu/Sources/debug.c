/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   debug.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clement <clement@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/24 15:22:01 by clement      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/27 18:01:32 by clement     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/malloc.h"

void		ft_print_region()
{
	t_region	*region_ptr;
	t_chunk		*chunk_ptr;
	int			reg = 0;

	region_ptr = g_region;
	while (region_ptr)
	{
		if (region_ptr->used)
			printf("START = %d\tREG\t%d\tUSED\t%d / %d\t%d\tADD\t%pHEAP\t%p\n", region_ptr->start, reg, region_ptr->used, region_ptr->size, region_ptr->type, region_ptr, region_ptr->heap);
		reg++;
		region_ptr = region_ptr->next;
	}
	system("clear");
}
