/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hmap_data_transfer.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhongu <fhongu@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 13:01:04 by fhongu            #+#    #+#             */
/*   Updated: 2023/11/28 21:41:22 by fhongu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	add_new(t_hashmap *hmap, void *key, void *value, size_t len);

void	ft_hmap_add(t_hashmap *hmap, void *key, void *value, size_t len)
{
	if (!ft_hmap_get(hmap, key, len))
		add_new(hmap, key, value, len);
	else
		ft_hmap_edit(hmap, key, value, len);
}

static void	add_new(t_hashmap *hmap, void *key, void *value, size_t len)
{
	t_ushort	hash;
	t_key_value	*keyval;
	t_list		*element;

	if (hmap->count + 1 >= hmap->size * HASHMAP_MAX_LOAD)
		hmap = ft_hmap_resize(hmap);
	hmap->count += 1;
	hash = ft_hash((unsigned char *) key, len) % hmap->size;
	if (!hmap->map[hash])
		hmap->map[hash] = ft_lstnew(NULL);
	keyval = malloc(sizeof (t_key_value));
	if (!keyval)
		return (ft_hmap_free(hmap));
	keyval->key = key;
	keyval->value = value;
	element = malloc (sizeof (t_list));
	if (!element)
		return (ft_hmap_free(hmap));
	element->content = keyval;
	element->next = NULL;
	ft_lstadd_back(&hmap->map[hash], element);
}

void	ft_hmap_edit(t_hashmap *hmap, void *key, void *value, size_t len)
{
	t_ushort	hash;
	t_list		*list;
	t_key_value	*keyval;

	hash = ft_hash((unsigned char *) key, len) % hmap->size;
	list = hmap->map[hash];
	while (list->next != NULL)
	{
		keyval = (t_key_value *) list->content;
		if (ft_strncmp(keyval->key, key, ft_strlen(key)) == 0)
		{
			((t_key_value *) list->content)->value = value;
			return ;
		}
		list = list->next;
	}
}

void	ft_hmap_delete(t_hashmap *hmap, void *key, size_t len)
{
	t_ushort	hash;
	t_list		*list;
	t_list		*prev;
	t_key_value	*keyval;

	hash = ft_hash((unsigned char *) key, len) % hmap->size;
	list = hmap->map[hash];
	prev = NULL;
	while (list->next != NULL)
	{
		keyval = (t_key_value *) list->content;
		if (ft_strncmp(keyval->key, key, ft_strlen(key)) == 0)
		{
			if (prev != NULL)
				prev->next = list->next;
			ft_lstdelone(list, hmap->del);
			return ;
		}
		prev = list;
		list = list->next;
	}
}

void	*ft_hmap_get(t_hashmap *hmap, void *key, size_t len)
{
	t_ushort	hash;
	t_list		*list;
	t_key_value	*keyval;

	hash = ft_hash((unsigned char *) key, len) % hmap->size;
	list = hmap->map[hash];
	while (list->next != NULL)
	{
		keyval = (t_key_value *) list->content;
		if (ft_strncmp(keyval->key, key, ft_strlen(key)) == 0)
		{
			return (keyval->value);
		}
		list = list->next;
	}
	return (NULL);
}
