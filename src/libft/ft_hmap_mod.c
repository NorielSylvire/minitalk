/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hmap_mod.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhongu <fhongu@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 11:59:34 by fhongu            #+#    #+#             */
/*   Updated: 2023/11/28 21:10:11 by fhongu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @file ft_hmap_mod,c
 * @brief Provides functions that modify a t_hashmap
 * This file contains functions that modify hashmaps. For example functions
 * to create and free hashmaps, and functions to add or remove elements.
 */

#include "libft.h"

t_hashmap	*ft_hmap_new(void (*del)(void *))
{
	t_hashmap	*hmap;

	hmap = malloc(sizeof (t_hashmap));
	if (!hmap)
		return (NULL);
	hmap->del = del;
	hmap->count = 0;
	hmap->size = HASHMAP_DEFAULT_SIZE;
	hmap->map = ft_calloc(HASHMAP_DEFAULT_SIZE, sizeof (t_list));
	return (hmap);
}

void	ft_hmap_free(t_hashmap *hmap)
{
	int	i;

	i = 0;
	while (i < hmap->size)
	{
		if (hmap->map[i] != NULL)
			ft_lstclear(&hmap->map[i], hmap->del);
		i++;
	}
}

t_hashmap	*ft_hmap_resize(t_hashmap *hmap)
{
	t_hashmap	*resized_hmap;
	int			i;

	resized_hmap = malloc(sizeof (t_hashmap));
	if (!resized_hmap)
		return (ft_hmap_free(hmap), NULL);
	resized_hmap->del = hmap->del;
	resized_hmap->count = hmap->count;
	resized_hmap->size = hmap->size * HASHMAP_RESIZE_FACTOR;
	resized_hmap->map = ft_calloc(resized_hmap->size, sizeof (t_list));
	if (!resized_hmap->map)
	{
		ft_hmap_free(hmap);
		ft_hmap_free(resized_hmap);
		return (NULL);
	}
	i = 0;
	while (i < hmap->size)
	{
		resized_hmap->map[i] = hmap->map[i];
		hmap->map[i++] = NULL;
	}
	ft_free((void **)hmap->map);
	ft_free((void **)&hmap);
	return (resized_hmap);
}

t_ushort	ft_hash(unsigned char *key, size_t nbytes)
{
	int			i;
	t_ushort	hash;

	hash = 0;
	i = 0;
	while (i++ < (int) nbytes)
	{
		hash += *key++;
	}
	return (hash);
}
