/*
 * (C) Copyright 2013 Xilinx, Inc.
 *
 * Configuration for Zynq Evaluation and Development Board - ZedBoard
 * See zynq-common.h for Zynq common configs
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#ifndef __CONFIG_ZYNQ_ZTURN_H
#define __CONFIG_ZYNQ_ZTURN_H

#define	PHYS_SDRAM_1_SIZE	(512 * 1024 * 1024)

#define CONFIG_ZYNQ_SERIAL_UART1
#define CONFIG_ZYNQ_GEM0
#define CONFIG_ZYNQ_GEM_PHY_ADDR0	0

#define CONFIG_SYS_NO_FLASH

#define CONFIG_ZYNQ_USB
#define CONFIG_ZYNQ_SDHCI0
#define CONFIG_ZYNQ_QSPI

/*
 * QSPI flash mapping
 *
 *   start       end      size     name
 * ---------------------------------------
 * 0x0000000 - 0x0100000  0x100000  boot.bin(1MB)
 * 0x0100000 - 0x0120000  0x020000  ubootenv(128KB)
 * 0x0120000 - 0x0720000  0x600000  bitstream(6MB)
 * 0x0720000 - 0x0D20000  0x600000  uImage(6MB)
 * 0x0D20000 - 0x0D40000  0x020000  devicetree(128KB)
 * 0x0D40000 - 0x1940000  0xC00000  ramdisk(12MB)
 * 0x1940000 - 0x1FFFFFF  0x6C0000  data(6.75MB)
 */
#define CONFIG_ENV_OFFSET 		0x010C0000	/* environment start addr in spi flash */
#define CONFIG_ENV_SIZE			(128*1024)	/* environment size is 128KB    */
#define CONFIG_ENV_SECT_SIZE	(64*1024u)	/* S25FL256 is 64KB sector type */

#define CONFIG_ZYNQ_BOOT_FREEBSD
#define CONFIG_DEFAULT_DEVICE_TREE	zynq-myd

#define CONFIG_IPADDR	192.168.1.55
#define CONFIG_SERVERIP	192.168.1.13

#define CONFIG_AUTOBOOT_KEYED 1 
#define CONFIG_AUTOBOOT_DELAY_STR "passwd"
#define CONFIG_AUTOBOOT_STOP_STR "\x1b"

#define CONFIG_EXTRA_ENV_SETTINGS	\
	"blr_fname=BOOT.bin\0" \
	"env_fname=uEnt.txt\0" \
	"dtb_fname=devicetree.dtb\0" \
	"bit_fname=system.bit\0" \
	"knl_fname=uImage\0" \
	"rfs_fname=rootfs.jffs2\0" \
	"blr_loadaddr=0x01000000\0" \
	"env_loadaddr=0x010C0000\0" \
	"dtb_loadaddr=0x010E0000\0" \
	"bit_loadaddr=0x03000000\0" \
	"knl_loadaddr=0x01100000\0" \
	"rfs_loadaddr=0x01600000\0" \
	"blr_spifaddr=0x00000000\0" \
	"env_spifaddr=0x000C0000\0" \
	"dtb_spifaddr=0x000E0000\0" \
	"bit_spifaddr=0x02000000\0" \
	"knl_spifaddr=0x00100000\0" \
	"rfs_spifaddr=0x00600000\0" \
	"blr_partsize=0x000C0000\0" \
	"env_partsize=0x00020000\0" \
	"dtb_partsize=0x00020000\0" \
	"bit_partsize=0x00D00000\0" \
	"knl_partsize=0x00500000\0" \
	"rfs_partsize=0x01400000\0" \
	"flash_blr=echo Flash Bootloader......; mw.b ${blr_loadaddr} 0xFF ${blr_partsize}; fatload mmc 0 ${blr_loadaddr} ${blr_fname}; sf write ${blr_loadaddr} ${blr_spifaddr} ${blr_partsize}\0" \
	"flash_dtb=echo Flash Devicetree......; mw.b ${dtb_loadaddr} 0xFF ${dtb_partsize}; fatload mmc 0 ${dtb_loadaddr} ${dtb_fname}; sf write ${dtb_loadaddr} ${dtb_spifaddr} ${dtb_partsize}\0" \
	"flash_bit=echo Flash Bitstream.......; mw.b ${bit_loadaddr} 0xFF ${bit_partsize}; fatload mmc 0 ${bit_loadaddr} ${bit_fname}; sf write ${bit_loadaddr} ${bit_spifaddr} ${bit_partsize}\0" \
	"flash_knl=echo Flash Kernel..........; mw.b ${knl_loadaddr} 0xFF ${knl_partsize}; fatload mmc 0 ${knl_loadaddr} ${knl_fname}; sf write ${knl_loadaddr} ${knl_spifaddr} ${knl_partsize}\0" \
	"flash_rfs=echo Flash Rootfs..........; mw.b ${rfs_loadaddr} 0xFF ${rfs_partsize}; fatload mmc 0 ${rfs_loadaddr} ${rfs_fname}; sf write ${rfs_loadaddr} ${rfs_spifaddr} ${rfs_partsize}\0" \
	"updatesys=sf probe 0 0 0; sf erase 0 0x4000000; run flash_blr; run flash_dtb; run flash_bit; run flash_knl; run flash_rfs; echo Flash Programming DONE \0" \
	"sf_boot=sf probe 0 0 0; " \
		"sf read ${bit_loadaddr} ${bit_spifaddr} ${bit_partsize}; " \
		"fpga loadb 0 ${bit_loadaddr} ${bit_partsize}; " \
		"sf read ${knl_loadaddr} ${knl_spifaddr} ${knl_partsize}; " \
		"sf read ${dtb_loadaddr} ${dtb_spifaddr} ${dtb_partsize}; " \
		"run jffs2_args; " \
		"bootm ${knl_loadaddr} - ${dtb_loadaddr}\0 " \
	"jffs2_args=setenv bootargs console=ttyPS0,115200 " \
		"root=/dev/mtdblock5 rootfstype=jffs2 rw rootwait ${optargs} \0" \
	"loadbootenv=fatload mmc 0 ${env_loadaddr} ${env_fname}\0" \
	"importbootenv=echo Importing environment from SD ...; " \
		"env import -t ${env_loadaddr} $filesize\0" \
	"uenvboot=" \
		"if run loadbootenv; then " \
			"echo Loaded environment from ${env_fname}; " \
			"run importbootenv; " \
		"fi; " \
		"if test -n $uenvcmd; then " \
			"echo Running uenvcmd ...; " \
			"run uenvcmd; " \
		"fi\0" \
	"sd_boot=if mmcinfo; then " \
		"run uenvboot; " \
		"mmc rescan; " \
		"mmc dev 0; " \
		"fatload mmc 0 ${bit_loadaddr} ${bit_fname}; " \
		"fpga loadb 0 ${bit_loadaddr} ${bit_partsize}; " \
		"fatload mmc 0 ${knl_loadaddr} ${knl_fname}; " \
		"fatload mmc 0 ${dtb_loadaddr} ${dtb_fname}; " \
		"run ext4_args; " \
		"bootm ${knl_loadaddr} - ${dtb_loadaddr}; " \
		"fi\0" \
	"ext4_args=setenv bootargs console=ttyPS0,115200 " \
		"root=/dev/mmcblk0p2 rw earlyprintk rootfstype=ext4 rootwait ${optargs} \0" \
	"net_boot=\0" \
	"ram_boot=\0" \

#include <configs/zynq_common.h>

#endif /* __CONFIG_ZYNQ_ZED_H */
