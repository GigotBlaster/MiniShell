/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: npetitpi <npetitpi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:25:33 by npetitpi          #+#    #+#             */
/*   Updated: 2023/10/26 13:25:34 by npetitpi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftfull.h"

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*begin;

	begin = *alst;
	if (!begin)
	{
		*alst = new;
		return ;
	}
	while (begin && begin->next)
		begin = begin->next;
	begin->next = new;
}
