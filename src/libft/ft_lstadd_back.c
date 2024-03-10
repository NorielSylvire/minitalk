/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhongu <fhongu@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/09 19:23:19 by fhongu            #+#    #+#             */
/*   Updated: 2023/11/26 12:52:39 by fhongu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Adds an element to the end of the list.
 */
void	ft_lstadd_back(t_list **lst, t_list *new_lmn)
{
	t_list	*iter;

	if (!*lst)
	{
		*lst = new_lmn;
		return ;
	}
	iter = *lst;
	while (iter->next != NULL)
	{
		iter = iter->next;
	}
	iter->next = new_lmn;
}
