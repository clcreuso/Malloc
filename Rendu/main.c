/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clement <clement@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/07 17:47:26 by clement      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/17 14:43:02 by clement     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/resource.h>
#include "Includes/malloc.h"

void	*ft_malloc(size_t size);

int main()
{
	char *end;
	char *start;
	char *prev;

	start = (char *)ft_malloc(12);
	prev = start;
	while (1)
	{
		end = (char *)ft_malloc(12);

		printf("DIFF\t%llu\n", (uint64_t)end - (uint64_t)prev);
		printf("TOTAL\t%llu\n", (uint64_t)end - (uint64_t)start);
		
		prev = end;
	}
	return 0;
}
