/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   tools_02.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clcreuso <clcreuso@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/27 15:52:57 by clement      #+#   ##    ##    #+#       */
/*   Updated: 2019/06/03 11:36:20 by clcreuso    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "malloc.h"

int		ft_putchar(char c)
{
	write(1, &c, 1);
	return (1);
}

int		ft_strlen(const char *s)
{
	int len;

	len = 0;
	while (*s++)
		len++;
	return (len);
}

void	*ft_memset(void *s, int c, size_t n)
{
	char *d;

	d = (char*)s;
	if (n)
		while (n--)
			*d++ = c;
	return (s);
}

char	*ft_memncpy(char *d, const char *s, size_t n)
{
	size_t a;

	a = 0;
	while (a < n)
	{
		d[a] = s[a];
		a++;
	}
	return (d);
}

void	ft_putnbr(int n)
{
	if (n == -2147483648)
	{
		write(0, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		ft_putchar('-');
		n = -n;
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putchar(n % 10 + '0');
	}
	if (n < 10)
		ft_putchar(n + '0');
}
