/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   show_alloc_mem.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/28 11:12:19 by clement      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/03 11:36:20 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

char	*write_hexa_helper(char *dest, u_int64_t x)
{
	if (x >= 16)
		dest = write_hexa_helper(dest, (x / 16));
	*dest++ = "0123456789ABCDEF"[x & 15];
	return (dest);
}

void	write_hexa(u_int64_t x)
{
	char dest[16];

	*write_hexa_helper(dest, x) = '\0';
	write(1, "0x", 2);
	write(1, dest, ft_strlen(dest));
}

void	show_region_header(t_region *region)
{
	if (region->type == TINY)
		write(1, "TINY", 4);
	if (region->type == SMALL)
		write(1, "SMALL", 5);
	if (region->type == LARGE)
		write(1, "LARGE", 5);
	write(1, " : ", 3);
	write_hexa((u_int64_t)region->heap);
	write(1, "\n", 1);
}

int		show_chunks(t_chunk *chunk)
{
	int		total;
	t_chunk	*ptr;

	total = 0;
	ptr = chunk;
	while (ptr)
	{
		if (!(IS_FREE(ptr->size)))
		{
			total += ptr->size - (sizeof(struct s_chunk) + 1);
			write_hexa((u_int64_t)ptr + sizeof(struct s_chunk));
			write(1, " - ", 3);
			write_hexa((u_int64_t)ptr + (ptr->size - 1));
			write(1, " : ", 3);
			ft_putnbr(ptr->size - (sizeof(struct s_chunk) + 1));
			write(1, " octets\n", 8);
		}
		ptr = ptr->next;
	}
	return (total);
}

void	show_alloc_mem(void)
{
	t_region	*region;
	int			total;

	total = 0;
	if (!(region = g_region))
	{
		write(1, "no memory allocation\n", 21);
		return ;
	}
	while (region)
	{
		if (region->type)
		{
			show_region_header(region);
			total += show_chunks(region->heap);
		}
		region = region->next;
	}
	write(1, "Total : ", 8);
	ft_putnbr(total);
	write(1, " octets\n", 8);
}
