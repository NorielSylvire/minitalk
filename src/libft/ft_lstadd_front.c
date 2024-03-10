/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fhongu <fhongu@student.42madrid.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/08 22:12:39 by fhongu            #+#    #+#             */
/*   Updated: 2023/11/26 12:53:44 by fhongu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief Adds an element to the start of the list.
 */
void	ft_lstadd_front(t_list **lst, t_list *new_lmn)
{
	new_lmn->next = *lst;
	*lst = new_lmn;
}
