/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ciglesia <ciglesia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/13 23:08:24 by ciglesia          #+#    #+#             */
/*   Updated: 2021/06/13 23:53:12 by ciglesia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void	print_64header(Elf64_Ehdr elf_64, char **type)
{
	ft_printf("  Type:                              ");
	if (elf_64.e_type < 5)
		ft_printf("%s\n", type[elf_64.e_type]);
	else
		ft_printf("Processor Specific: (%.2x)\n", elf_64.e_type);
	ft_printf("  Machine:                           %#x\n", elf_64.e_machine);
	ft_printf("  Version:                           %#x\n", elf_64.e_version);
	ft_printf("  Entry point address:               %#x\n", elf_64.e_entry);
	ft_printf("  Start of program headers:          ");
	ft_printf("%d (bytes into file)\n", elf_64.e_phoff);
	ft_printf("  Start of section headers:          ");
	ft_printf("%d (bytes into file)\n", elf_64.e_shoff);
	ft_printf("  Flags:                             0x%x\n", elf_64.e_flags);
	ft_printf("  Size of this header:               ");
	ft_printf("%d (bytes)\n", elf_64.e_ehsize);
	ft_printf("  Size of program headers:           ");
	ft_printf("%d (bytes)\n", elf_64.e_phentsize);
	ft_printf("  Number of program headers:         %d\n", elf_64.e_phnum);
	ft_printf("  Size of section headers:           ");
	ft_printf("%d (bytes)\n", elf_64.e_shentsize);
	ft_printf("  Number of section headers:         %d\n", elf_64.e_shnum);
	ft_printf("  Section header string table index: %d\n", elf_64.e_shstrndx);
}

static void	print_32header(Elf32_Ehdr elf_32, char **type)
{
	ft_printf("  Type:                              ");
	if (elf_32.e_type < 5)
		ft_printf("%s\n", type[elf_32.e_type]);
	else
		ft_printf("Processor Specific: (%.2x)\n", elf_32.e_type);
	ft_printf("  Machine:                           %#x\n", elf_32.e_machine);
	ft_printf("  Version:                           %#x\n", elf_32.e_version);
	ft_printf("  Entry point address:               %#x\n", elf_32.e_entry);
	ft_printf("  Start of program headers:          ");
	ft_printf("%d (bytes into file)\n", elf_32.e_phoff);
	ft_printf("  Start of section headers:          ");
	ft_printf("%d (bytes into file)\n", elf_32.e_shoff);
	ft_printf("  Flags:                             0x%x\n", elf_32.e_flags);
	ft_printf("  Size of this header:               ");
	ft_printf("%d (bytes)\n", elf_32.e_ehsize);
	ft_printf("  Size of program headers:           ");
	ft_printf("%d (bytes)\n", elf_32.e_phentsize);
	ft_printf("  Number of program headers:         %d\n", elf_32.e_phnum);
	ft_printf("  Size of section headers:           ");
	ft_printf("%d (bytes)\n", elf_32.e_shentsize);
	ft_printf("  Number of section headers:         %d\n", elf_32.e_shnum);
	ft_printf("  Section header string table index: %d\n", elf_32.e_shstrndx);
}

static void	print_magic(t_elf *elf, char **arch, char **endian, char **osabi)
{
	int		i;

	ft_printf("ELF Header:\n");
	ft_printf("  Magic:   "GREEN);
	i = 0;
	while (i < EI_NIDENT)
		ft_printf("%.2x ", elf->identifier[i++]);
	ft_printf(E0M"\n  Class:                             ");
	ft_printf("%s\n", arch[elf->identifier[EI_CLASS]]);
	ft_printf("  Data:                              ");
	ft_printf("2's complement, %s endian\n", endian[elf->identifier[EI_DATA]]);
	ft_printf("  Version:                           1 (current)\n");
	ft_printf("  OS/ABI:                            ");
	ft_printf("%s\n", osabi[elf->identifier[EI_OSABI]]);
	ft_printf("  ABI Version:                       %d\n", elf->identifier[8]);
}

/*
**	ELF_TYPE:
**	0x00 	ET_NONE
**	0x01 	ET_REL
**	0x02 	ET_EXEC
**	0x03 	ET_DYN
**	0x04 	ET_CORE
**	0xFE00 	ET_LOOS
**	0xFEFF 	ET_HIOS
**	0xFF00 	ET_LOPROC
**	0xFFFF 	ET_HIPROC
**
**	ELF_OSABI:
**	0x00 	System V
**	0x01 	HP-UX
**	0x02 	NetBSD
**	0x03 	Linux
**	0x04 	GNU Hurd
**	0x06 	Solaris
**	0x07 	AIX
**	0x08 	IRIX
**	0x09 	FreeBSD
**	0x0A 	Tru64
**	0x0B 	Novell Modesto
**	0x0C 	OpenBSD
**	0x0D 	OpenVMS
**	0x0E 	NonStop Kernel
**	0x0F 	AROS
**	0x10 	Fenix OS
**	0x11 	CloudABI
**	0x12 	Stratus Technologies OpenVOS
*/

void	print_header(t_elf *elf)
{
	char	*arch[3] = {NULL, "ELF32", "ELF64"};
	char	*endian[3] = {NULL, "little", "big"};
	char	*osabi[18] = {"UNIX - System V", "HP-UX", "NetBSD", "Linux",
						  "GNU Hurd", "Solaris", "AIX", "IRIX", "FreeBSD",
						  "Tru64", "Novell Modesto", "OpenBSD", "OpenVMS",
						  "NonStop Kernel", "AROS", "Fenix OS", "Cloud ABI",
						  "Stratus Technologies OpenVOS"};
	char	*type[9] = {"NONE (None)", "REL (Relocatable file)",
						"EXEC (Executable file)", "DYN (Shared object file)",
						"CORE (Core file)"};

	print_magic(elf, arch, endian, osabi);
	if (elf->class == ELFCLASS64)
		print_64header(elf->elf_64, type);
	else if (elf->class == ELFCLASS32)
		print_32header(elf->elf_32, type);
}
