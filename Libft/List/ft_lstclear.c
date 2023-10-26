/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:25:39 by npetitpi          #+#    #+#             */
/*   Updated: 2023/10/26 13:25:40 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*beg;
	t_list	*save;

	if (!lst)
		return ;
	beg = *lst;
	while (beg)
	{
		save = beg->next;
		ft_lstdelone(beg, del);
		beg = save;
	}
	*lst = NULL;
}
