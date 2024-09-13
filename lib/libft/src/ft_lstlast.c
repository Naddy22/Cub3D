/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jdemers <jdemers@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 14:08:28 by jdemers           #+#    #+#             */
/*   Updated: 2024/09/13 17:19:45 by jdemers          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


t_list	*ft_lstlast(t_list *lst)
{
	if (!lst || !lst->next)
		return (lst);
	return (ft_lstlast(lst->next));
}
t_list	*ft_lstfirst(t_list *lst)
{
	if (!lst || !lst->prev)
		return (lst);
	return (ft_lstfirst(lst->prev));
}