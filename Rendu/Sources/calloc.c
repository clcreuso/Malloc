/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   calloc.c                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/29 14:36:01 by clcreuso     #+#   ##    ##    #+#       */
/*   Updated: 2019/05/29 15:43:38 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/malloc.h"

void    *calloc(size_t count, size_t size)
{
    size_t      total;
	char        *p;

    total = count * size;
    if (!(p = (char*)malloc(total)))
        return NULL;
	return (ft_memset(p, 0, total));
}