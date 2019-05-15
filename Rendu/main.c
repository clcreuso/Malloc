/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clement <clement@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/07 17:47:26 by clement      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/15 17:46:15 by clement     ###    #+. /#+    ###.fr     */
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
	int a = 0;
	char *str = (char *)ft_malloc(1);
	
	printf("adresse = %p\nint = %d\n", str, (int)str);

	str = (char *)ft_malloc(993);
	
	printf("adresse = %p\nint = %d\n", str, (int)str);
	
	str = (char *)ft_malloc(127000);
	
	printf("adresse = %p\nint = %d\n", str, (int)str);
	
	str = (char *)ft_malloc(1);
	
	
	
	return 0;
}
