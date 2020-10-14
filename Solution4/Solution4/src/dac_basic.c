/**
 * \file
 *
 * \brief DAC Basic driver implementation.
 *
 (c) 2020 Microchip Technology Inc. and its subsidiaries.

    Subject to your compliance with these terms,you may use this software and
    any derivatives exclusively with Microchip products.It is your responsibility
    to comply with third party license terms applicable to your use of third party
    software (including open source software) that may accompany Microchip software.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 */

/**
 * \defgroup doc_driver_dac_basic DAC Basic Driver
 * \ingroup doc_driver_dac
 *
 * \section doc_driver_dac_rev Revision History
 * - v0.0.0.1 Initial Commit
 *
 *@{
 */
#include <dac_basic.h>

/**
 * \brief Initialize DAC interface
 * If module is configured to disabled state, the clock to the DAC is disabled
 * if this is supported by the device's clock system.
 *
 * \return Initialization status.
 * \retval 0 the DAC init was successful
 * \retval 1 the DAC init was not successful
 */
int8_t DAC_0_init()
{

	DAC0.DATA = 0x0 << DAC_DATA_gp; /* DATA Register: 0x0 */

	DAC0.CTRLA = 1 << DAC_ENABLE_bp      /* DAC Enable: enabled */
	             | 1 << DAC_OUTEN_bp     /* Output Buffer Enable: enabled */
	             | 0 << DAC_RUNSTDBY_bp; /* Run in Standby Mode: disabled */

	return 0;
}

/**
 * \brief Enable DAC_0
 * 1. If supported by the clock system, enables the clock to the DAC
 * 2. Enables the DAC module by setting the enable-bit in the DAC control register
 *
 * \return Nothing
 */
void DAC_0_enable()
{
	DAC0.CTRLA |= DAC_ENABLE_bm;
}

/**
 * \brief Disable DAC_0
 * 1. Disables the DAC module by clearing the enable-bit in the DAC control register
 * 2. If supported by the clock system, disables the clock to the DAC
 *
 * \return Nothing
 */
void DAC_0_disable()
{
	DAC0.CTRLA &= ~DAC_ENABLE_bm;
}

/**
 * \brief Start a conversion on DAC_0
 *
 * \param[in] value The digital value to be converted to analogue voltage by the DAC
 *
 * \return Nothing
 */
void DAC_0_set_output(dac_resolution_t value)
{
	value     = value << DAC_DATA_gp;
	value     = value & 0xFFC0;
	DAC0.DATA = value;
}

/**
 * \brief Return the number of bits in the DAC resolution
 *
 * \return The number of bits in the DAC resolution
 */
uint8_t DAC_0_get_resolution()
{
	return 8;
}
