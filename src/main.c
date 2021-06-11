/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 22:32:16 by ciglesia          #+#    #+#             */
/*   Updated: 2021/06/09 22:48:15 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int	main(int ac, char **av)
{
	char	*obj;

	if (ac == 1)
		obj = "./a.out";
	else
		obj = av[1];
	printf("obj: %s\n", obj);
	return (EXIT_SUCCESS);
}
