/**
 * \file
 * \brief Alternate mbed TLS threading implementation for distortos
 *
 * \author Copyright (C) 2019 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#ifndef MBED_TLS_INTEGRATION_INCLUDE_THREADING_ALT_H_
#define MBED_TLS_INTEGRATION_INCLUDE_THREADING_ALT_H_

#include "distortos/C-API/Mutex.h"

#ifdef __cplusplus
extern "C"
{
#endif	/* def __cplusplus */

/*---------------------------------------------------------------------------------------------------------------------+
| global types
+---------------------------------------------------------------------------------------------------------------------*/

/** mbed TLS mutex */
typedef struct distortos_Mutex mbedtls_threading_mutex_t;

#ifdef __cplusplus
}	/* extern "C" */
#endif	/* def __cplusplus */

#endif	/* MBED_TLS_INTEGRATION_INCLUDE_THREADING_ALT_H_ */
