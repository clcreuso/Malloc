/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clement <clement@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/07 17:47:26 by clement      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/27 17:58:23 by clement     ###    #+. /#+    ###.fr     */
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
	char *str;
	
	while (1)
		str = (char*)ft_malloc(100000);

	return (0);
}
