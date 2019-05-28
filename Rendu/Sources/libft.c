/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   libft.c                                          .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clement <clement@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/27 15:52:57 by clement      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/28 11:42:38 by clement     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../Includes/malloc.h"

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
