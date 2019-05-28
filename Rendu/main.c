/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clement <clement@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/07 17:47:26 by clement      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/28 12:16:51 by clement     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "Includes/malloc.h"

int		main(void)
{
	char *str;

	str = (char*)malloc(1);
	int a = -1;

	while (a++ < 1)
		str[a] = ('A' + (a % 26));
	printf("%s\n", str);
	show_alloc_mem();
	return (0);
}
