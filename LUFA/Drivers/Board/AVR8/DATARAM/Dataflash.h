/*
             LUFA Library
     Copyright (C) Dean Camera, 2011.

  dean [at] fourwalledcubicle [dot] com
           www.lufa-lib.org
*/

/*
  Copyright 2011  Dean Camera (dean [at] fourwalledcubicle [dot] com)

  Permission to use, copy, modify, distribute, and sell this
  software and its documentation for any purpose is hereby granted
  without fee, provided that the above copyright notice appear in
  all copies and that both that the copyright notice and this
  permission notice and warranty disclaimer appear in supporting
  documentation, and that the name of the author not be used in
  advertising or publicity pertaining to distribution of the
  software without specific, written prior permission.

  The author disclaim all warranties with regard to this
  software, including all implied warranties of merchantability
  and fitness.  In no event shall the author be liable for any
  special, indirect or consequential damages or any damages
  whatsoever resulting from loss of use, data or profits, whether
  in an action of contract, negligence or other tortious action,
  arising out of or in connection with the use or performance of
  this software.
*/

/** \file
 *  \brief Board specific Dataflash driver header for Justy's EEPROM-based DATARAM board.
 *  \copydetails Group_Dataflash_DATARAM
 *
 *  \note This file should not be included directly. It is automatically included as needed by the dataflash driver
 *        dispatch header located in LUFA/Drivers/Board/Dataflash.h.
 *  This is a hack that assumes: 1 'chip', 2 pages, 512 bytes per page.  No chip selecting/deselecting required- simply
 *       returns bytes from EEPROM (and writes them if needed via this method- although that need not be done here. )
 */

/** \ingroup Group_Dataflash
 *  \defgroup Group_Dataflash_DATARAM DATARAM
 *  \brief Board specific Dataflash driver header for Justy's DATARAM board
 *
 *  Board specific Dataflash driver header for Justy's DATARAM board.
 *
 *  @{
 */

#ifndef __DATAFLASH_DATARAM_H__
#define __DATAFLASH_DATARAM_H__

	/* Includes: */
		#include "../../../../Common/Common.h"
		#include "../../../Misc/AT45DB321C.h"  // JJC: Not really needed but saves a lot of compile errors
		#include "../../../Peripheral/DATARAM.h"

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_DATAFLASH_H)
			#error Do not include this file directly. Include LUFA/Drivers/Board/Dataflash.h instead.
		#endif

	/* Private Interface - For use in library only: */
	#if !defined(__DOXYGEN__)
		/* Macros: */
			#define DATAFLASH_CHIPCS_MASK                (1 << 4)
			#define DATAFLASH_CHIPCS_DDR                 DDRB
			#define DATAFLASH_CHIPCS_PORT                PORTB
	#endif

	/* Public Interface - May be used in end-application: */
		/* Macros: */
			/** Constant indicating the total number of dataflash ICs mounted on the selected board. */
			#define DATAFLASH_TOTALCHIPS                 1 // Only one, and it's not a real chip.

			/** Mask for no dataflash chip selected. */
			#define DATAFLASH_NO_CHIP                    DATAFLASH_CHIPCS_MASK

			/** Mask for the first dataflash chip selected. */
			#define DATAFLASH_CHIP1                      0

			/** Internal main memory page size for the board's dataflash IC. */
      #define DATAFLASH_PAGE_SIZE                  1024 //512

			/** Total number of pages inside the board's dataflash IC. */
			#define DATAFLASH_PAGES                      1 //2

		/* Inline Functions: */
			/** Initializes the dataflash driver so that commands and data may be sent to an attached dataflash IC.
			 *  The microcontroller's SPI driver MUST be initialized before any of the dataflash commands are used.
			 */
			static inline void Dataflash_Init(void)
			{
			  // Nothing to do.
        return;
        DATAFLASH_CHIPCS_PORT |= DATAFLASH_CHIPCS_MASK;
			}

			/** Determines the currently selected dataflash chip.
			 *
			 *  \return Mask of the currently selected Dataflash chip, either \ref DATAFLASH_NO_CHIP if no chip is selected
			 *  or a DATAFLASH_CHIPn mask (where n is the chip number).
			 */
			static inline uint8_t Dataflash_GetSelectedChip(void) ATTR_ALWAYS_INLINE ATTR_WARN_UNUSED_RESULT;
			static inline uint8_t Dataflash_GetSelectedChip(void)
			{
				return (DATAFLASH_CHIPCS_PORT & DATAFLASH_CHIPCS_MASK);
			}

			/** Selects the given dataflash chip.
			 *
			 *  \param[in]  ChipMask  Mask of the Dataflash IC to select, in the form of DATAFLASH_CHIPn mask (where n is
			 *              the chip number).
			 */
			static inline void Dataflash_SelectChip(const uint8_t ChipMask) ATTR_ALWAYS_INLINE;
			static inline void Dataflash_SelectChip(const uint8_t ChipMask)
			{
				DATAFLASH_CHIPCS_PORT = ((DATAFLASH_CHIPCS_PORT & ~DATAFLASH_CHIPCS_MASK) | ChipMask);
			}

			/** Deselects the current dataflash chip, so that no dataflash is selected. */
			static inline void Dataflash_DeselectChip(void) ATTR_ALWAYS_INLINE;
			static inline void Dataflash_DeselectChip(void)
			{
			  // Nothing to do.
        return;
        Dataflash_SelectChip(DATAFLASH_NO_CHIP);
			}

			/** Selects a dataflash IC from the given page number, which should range from 0 to
			 *  ((DATAFLASH_PAGES * DATAFLASH_TOTALCHIPS) - 1). For boards containing only one
			 *  dataflash IC, this will select DATAFLASH_CHIP1. If the given page number is outside
			 *  the total number of pages contained in the boards dataflash ICs, all dataflash ICs
			 *  are deselected.
			 *
			 *  \param[in] PageAddress  Address of the page to manipulate, ranging from
			 *                          0 to ((DATAFLASH_PAGES * DATAFLASH_TOTALCHIPS) - 1).
			 */
			static inline void Dataflash_SelectChipFromPage(const uint16_t PageAddress)
			{
			  // Nothing to do.  (There's only one chip)
        return;
				Dataflash_DeselectChip();

				if (PageAddress >= DATAFLASH_PAGES)
				  return;

				Dataflash_SelectChip(DATAFLASH_CHIP1);
			}

			/** Toggles the select line of the currently selected dataflash IC, so that it is ready to receive
			 *  a new command.
			 */
			static inline void Dataflash_ToggleSelectedChipCS(void)
			{
			  // Nothing to do.
        return;
				uint8_t SelectedChipMask = Dataflash_GetSelectedChip();

				Dataflash_DeselectChip();
				Dataflash_SelectChip(SelectedChipMask);
			}

			/** Spin-loops while the currently selected dataflash is busy executing a command, such as a main
			 *  memory page program or main memory to buffer transfer.
			 */
			static inline void Dataflash_WaitWhileBusy(void)
			{
			  // This shouldn't be do anything, as DATARAM calls block
        return;
				Dataflash_ToggleSelectedChipCS();
				Dataflash_SendByte(DF_CMD_GETSTATUS);
				while (!(Dataflash_ReceiveByte() & DF_STATUS_READY));
				Dataflash_ToggleSelectedChipCS();
			}

			/** Sends a set of page and buffer address bytes to the currently selected dataflash IC, for use with
			 *  dataflash commands which require a complete 24-bit address.
			 *
			 *  \param[in] PageAddress  Page address within the selected dataflash IC
			 *  \param[in] BufferByte   Address within the dataflash's buffer
			 */
			static inline void Dataflash_SendAddressBytes(uint16_t PageAddress,
			                                              const uint16_t BufferByte)
			{
        // Set the address - with only one page, the address is simply BufferByte
        DATARAM_SendAddress(BufferByte);
				//Dataflash_SendByte(PageAddress >> 6);
				//Dataflash_SendByte((PageAddress << 2) | (BufferByte >> 8));
				//Dataflash_SendByte(BufferByte);
			}

#endif

/** @} */

