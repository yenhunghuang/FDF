/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yehuang <yenhang1@gmail.co>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 15:33:26 by yehuang           #+#    #+#             */
/*   Updated: 2019/07/26 22:47:47 by yehuang          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	cleanup(t_list *lst)
{
	t_list	*tmp;

	while (lst)
	{
		tmp = lst->next;
		ft_memdel((void **)&lst);
		lst = tmp;
	}
}

t_list		*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*elem;
	t_list	*first;

	if (lst)
	{
		elem = ft_lstnew(lst->content, lst->content_size);
		if (elem == NULL)
			return (NULL);
		elem = (*f)(elem);
		first = elem;
		while (lst->next)
		{
			lst = lst->next;
			elem->next = ft_lstnew(lst->content, lst->content_size);
			if (elem->next == NULL)
			{
				cleanup(first);
				return (NULL);
			}
			elem->next = (*f)(elem->next);
			elem = elem->next;
		}
		return (first);
	}
	return (NULL);
}
