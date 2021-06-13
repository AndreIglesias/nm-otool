/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 22:34:44 by ciglesia          #+#    #+#             */
/*   Updated: 2021/06/13 23:14:51 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <linux/elf.h>
# include <fcntl.h>

typedef struct s_elf
{
	Elf32_Ehdr		elf_32;
	Elf64_Ehdr		elf_64;
	unsigned char	identifier[EI_NIDENT];
	unsigned char	class;
	char			*obj;
	int				fd;
}	t_elf;

/*
**	Display
*/

void		print_header(t_elf *elf);

#endif
