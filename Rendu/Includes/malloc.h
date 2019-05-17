/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   malloc.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clement <clement@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/07 17:47:48 by clement      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/17 14:52:10 by clement     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stddef.h>
# include <unistd.h>

# define TINY 				0

# define TINY_BYTE_MIN		1
# define TINY_BYTE_MAX		992
# define TINY_PAGE_NUMBER	16
# define TINY_MMAP_SIZE		TINY_PAGE_NUMBER * getpagesize()
# define TINY_SIZE(x) 		(((x) >= TINY_BYTE_MIN) && ((x) <= TINY_BYTE_MAX))

# define SMALL 				1

# define SMALL_BYTE_MIN		993
# define SMALL_BYTE_MAX     127000
# define SMALL_PAGE_NUMBER 	2048
# define SMALL_MMAP_SIZE	SMALL_PAGE_NUMBER * getpagesize()
# define SMALL_SIZE(x) 		(((x) >= SMALL_BYTE_MIN) && ((x) <= SMALL_BYTE_MAX))

# define LARGE 				2

# define LARGE_BYTE_MIN 	127001
# define LARGE_SIZE(x) 		(((x) >= LARGE_BYTE_MIN))

# define IS_FREE(x)			(((x) % 2) == 0)
# define REGION_SIZE(x) 	(((x) == TINY) ? (TINY_MMAP_SIZE) : (SMALL_MMAP_SIZE))

typedef struct 				s_chunk {
	int 		chunk_size;
	int 		alloc_size;
	void		*next;
}							t_chunk;

#endif
