/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   malloc.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: clement <clement@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/05/07 17:47:48 by clement      #+#   ##    ##    #+#       */
/*   Updated: 2019/05/27 16:02:40 by clement     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef MALLOC_H
# define MALLOC_H

# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/mman.h>

# define ZERO				0

# define TINY 				1

# define REGION_MMAP_SIZE	4096

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

# define IS_FREE(x)			(((x) % 2) == 0)

typedef struct 				s_chunk {
	size_t			size;
	void			*next;
	void			*region;
}							t_chunk;

typedef struct 				s_region {
	int				type;
	int				size;
	int				used;
	int				start;
	void			*heap;
	void			*next;
	void			*prev;
}							t_region;

t_region					*g_region;

void		*ft_malloc(size_t size);
t_region	*new_metadata_region();
void		init_metadata_region(void);
void		ft_print_region();
int			region_type(size_t size);
int			region_size(size_t size, int type);
size_t		round_size(size_t size);
void		*mmap_page(size_t size);
void		*init_chunks_region(t_region *region, size_t size, int type);
t_chunk		*find_free_chunk(t_region *region, size_t size);
void		*resize_chunk(t_chunk *chunk, size_t size);
t_region	*find_metadata_region(t_region *region, int type);
void		ft_free(void *ptr);
char		*ft_strncpy(char *d, const char *s, size_t n);
void		*ft_realloc(void *ptr, size_t size);


#endif
