/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   malloc.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clement <clement@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/07 17:47:48 by clement      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/28 12:18:22 by clement     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# define TINY 				1
# define TINY_BYTE_MIN		1
# define TINY_BYTE_MAX		1024
# define TINY_PAGE_NUMBER	32
# define TINY_MMAP_SIZE		TINY_PAGE_NUMBER * getpagesize()

# define SMALL 				2
# define SMALL_BYTE_MIN		1025
# define SMALL_BYTE_MAX     131072
# define SMALL_PAGE_NUMBER 	4096
# define SMALL_MMAP_SIZE	SMALL_PAGE_NUMBER * getpagesize()

# define LARGE 				4
# define LARGE_BYTE_MIN 	131073

# define REGION_MMAP_SIZE	4096
# define IS_FREE(x)			(((x) % 2) == 0)

# include <unistd.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/mman.h>
# include <sys/resource.h>

typedef struct	s_chunk {
	size_t			size;
	void			*next;
	void			*region;
}				t_chunk;

typedef struct	s_region {
	int				type;
	int				size;
	int				used;
	int				start;
	void			*heap;
	void			*next;
	void			*prev;
}				t_region;

t_region		*g_region;

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                  malloc.c                                  ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void			*large_malloc(t_region *region, size_t size);
void			*smart_malloc(size_t size, int type);
void			*malloc(size_t size);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                   free.c                                   ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void			free_region(t_region *region);
void			free_metadata(void);
void			free(void *ptr);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                  chunk.c                                   ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int				check_chunk_exist(void *ptr);
void			*init_chunks_region(t_region *region, size_t size, int type);
t_chunk			*find_free_chunk(t_region *region, size_t size);
void			*resize_chunk(t_chunk *chunk, size_t size);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                  libft.c                                   ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int				ft_strlen(const char *s);
char			*ft_strncpy(char *d, const char *s, size_t n);
void			ft_putnbr(int n);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                 realloc.c                                  ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

void			*realloc(void *ptr, size_t size);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                  region.c                                  ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

t_region		*find_metadata_region(t_region *region, int type);
t_region		*new_metadata_region(void);
void			init_metadata_region(void);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                                  tools.c                                   ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

int				region_type(size_t size);
int				region_size(size_t size, int type);
size_t			round_size(size_t size);
void			*mmap_page(size_t size);

/*
**┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓
**┃                              show_alloc_mem.c                              ┃
**┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛
*/

char			*write_hexa_helper(char *dest, u_int64_t x);
void			write_hexa(u_int64_t x);
void			show_region_header(t_region *region);
int				show_chunks(t_chunk *chunk);
void			show_alloc_mem(void);

#endif
