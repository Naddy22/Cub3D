/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:48:33 by jdemers           #+#    #+#             */
/*   Updated: 2024/09/13 15:34:14 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	(*del)(lst->data);
	free(lst);
}

void	ft_lstpop(t_list **lst, void (*del)(void *))
{
	t_list	*next;

	next = (*lst)->next;
	ft_lstdelone(*lst, del);
	next->prev = NULL;
	*lst = next;
}
