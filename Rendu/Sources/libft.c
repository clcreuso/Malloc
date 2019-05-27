/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   libft.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clement <clement@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/27 15:52:57 by clement      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/27 17:00:26 by clement     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/malloc.h"

char	*ft_strncpy(char *d, const char *s, size_t n)
{
	unsigned int a;

	a = 0;
	while (s[a] && a < n)
	{
		d[a] = s[a];
		a++;
	}
	while (a < n)
		d[a++] = '\0';
	return (d);
}
