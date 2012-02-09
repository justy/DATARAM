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
 *  \brief DATARAM Peripheral Driver (AVR8)
 *
 *  On-chip DATARAM driver for the 8-bit AVR microcontrollers.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the DATARAM driver
 *        dispatch header located in LUFA/Drivers/Peripheral/DATARAM.h.
 */

/** \ingroup Group_DATARAM
 *  \defgroup Group_DATARAM_AVR8 DATARAM Peripheral Driver (AVR8)
 *
 *  \section Sec_ModDescription Module Description
 *  Driver for the hardware DATARAM port available on most 8-bit AVR microcontroller models. This
 *  module provides an easy to use driver for the setup and transfer of data over the
 *  AVR's DATARAM port.
 *
 *  \note This file should not be included directly. It is automatically included as needed by the DATARAM driver
 *        dispatch header located in LUFA/Drivers/Peripheral/DATARAM.h.
 *
 *  \section Sec_ExampleUsage Example Usage
 *  The following snippet is an example of how this module may be used within a typical
 *  application.
 *
 *  \code
 *      // Initialize the DATARAM driver before first use
 *      DATARAM_Init(DATARAM_SPEED_FCPU_DIV_2 | DATARAM_ORDER_MSB_FIRST | DATARAM_SCK_LEAD_FALLING |
 *               DATARAM_SAMPLE_TRAILING | DATARAM_MODE_MASTER);
 *
 *      // Send several bytes, ignoring the returned data
 *      DATARAM_SendByte(0x01);
 *      DATARAM_SendByte(0x02);
 *      DATARAM_SendByte(0x03);
 *
 *      // Receive several bytes, sending a dummy 0x00 byte each time
 *      uint8_t Byte1 = DATARAM_ReceiveByte();
 *      uint8_t Byte2 = DATARAM_ReceiveByte();
 *      uint8_t Byte3 = DATARAM_ReceiveByte();
 *
 *      // Send a byte, and store the received byte from the same transaction
 *      uint8_t ResponseByte = DATARAM_TransferByte(0xDC);
 *  \endcode
 * 
 *  @{
 */

#ifndef __DATARAM_AVR8_H__
#define __DATARAM_AVR8_H__

	/* Includes: */
		#include "../../../Common/Common.h"
		#include <avr/eeprom.h>

	/* Enable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			extern "C" {
		#endif

	/* Preprocessor Checks: */
		#if !defined(__INCLUDE_FROM_DATARAM_H)
			#error Do not include this file directly. Include LUFA/Drivers/Peripheral/DATARAM.h instead.
		#endif



	/* Public Interface - May be used in end-application: */
		/* Macros: */
		
        int DATARAM_index;
			
		/* Inline Functions: */
			/** Initializes the DATARAM subsystem, ready for transfers. Must be called before calling any other
			 *  DATARAM routines.
			 *
			 *  \param[in] DATARAMOptions  DATARAM Options, a mask consisting of one of each of the \c DATARAM_SPEED_*,
			 *                         \c DATARAM_SCK_*, \c DATARAM_SAMPLE_*, \c DATARAM_ORDER_* and \c DATARAM_MODE_* masks.
			 */
			static inline void DATARAM_Init(void)
			{
			  // Simply initialise the memory index.
        DATARAM_index = 0;
			}
			
    	/** Sets the DATARAM address, ready for transfers. 
    	 *
    	 *  \param[in] DATARAMOptions  DATARAM Options, a mask consisting of one of each of the \c DATARAM_SPEED_*,
    	 *                         \c DATARAM_SCK_*, \c DATARAM_SAMPLE_*, \c DATARAM_ORDER_* and \c DATARAM_MODE_* masks.
    	 */
			static inline void DATARAM_SendAddress(const uint16_t BufferByte)
			{
        DATARAM_index = BufferByte;
			}

			/** Turns off the DATARAM driver, disabling and returning used hardware to their default configuration. */
			static inline void DATARAM_Disable(void)
			{
			// Nuffink
			}
			
			/** Retrieves the currently selected DATARAM mode, once the DATARAM interface has been configured.
			 *
			 *  \return \ref DATARAM_MODE_MASTER if the interface is currently in DATARAM Master mode, \ref DATARAM_MODE_SLAVE otherwise
			 */
			static inline uint8_t DATARAM_GetCurrentMode(void) ATTR_ALWAYS_INLINE;
			static inline uint8_t DATARAM_GetCurrentMode(void)
			{
				// Nuffink
        return 0;
				//return (SPCR & DATARAM_MODE_MASTER);
			}

			/** Sends and receives a byte through the DATARAM interface, blocking until the transfer is complete.
			 *
			 *  \param[in] Byte  Byte to send through the DATARAM interface.
			 *
			 *  \return Response byte from the attached DATARAM device.
			 */
			static inline uint8_t DATARAM_TransferByte(const uint8_t Byte) ATTR_ALWAYS_INLINE;
			static inline uint8_t DATARAM_TransferByte(const uint8_t Byte)
			{
			  // Write Byte to DATARAM_index's address in EEPROM
			  // TODO
			  // Return the byte
        return Byte;
				//SPDR = Byte;
				//while (!(SPSR & (1 << DATARAMF)));
				//return SPDR;
			}

			/** Sends a byte through the DATARAM interface, blocking until the transfer is complete. The response
			 *  byte sent to from the attached DATARAM device is ignored.
			 *
			 *  \param[in] Byte  Byte to send through the DATARAM interface.
			 */
			static inline void DATARAM_SendByte(const uint8_t Byte) ATTR_ALWAYS_INLINE;
			static inline void DATARAM_SendByte(const uint8_t Byte)
			{
			  // Write Byte to DATARAM_index's address in EEPROM
			  // TODO
				//SPDR = Byte;
				//while (!(SPSR & (1 << DATARAMF)));
			}

			/** Sends a dummy byte through the DATARAM interface, blocking until the transfer is complete. The response
			 *  byte from the attached DATARAM device is returned.
			 *
			 *  \return The response byte from the attached DATARAM device.
			 */
			static inline uint8_t DATARAM_ReceiveByte(void) ATTR_ALWAYS_INLINE ATTR_WARN_UNUSED_RESULT;
			static inline uint8_t DATARAM_ReceiveByte(void)
			{
			  // Read DATARAM_index's address's byte from EEPROM
			  // TODO
			  // Return the byte
        return 0;
				//SPDR = 0x00;
				//while (!(SPSR & (1 << DATARAMF)));
				//return SPDR;
			}

	/* Disable C linkage for C++ Compilers: */
		#if defined(__cplusplus)
			}
		#endif

#endif

/** @} */

