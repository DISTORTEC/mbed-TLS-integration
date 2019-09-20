/**
 * \file
 * \brief Definitions of threading-related functions for mbed TLS
 *
 * \author Copyright (C) 2019 Kamil Szczygiel http://www.distortec.com http://www.freddiechopin.info
 *
 * \par License
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at http://mozilla.org/MPL/2.0/.
 */

#include "mbedtls/threading.h"

#include "distortos/assert.h"
#include "distortos/BIND_LOW_LEVEL_INITIALIZER.h"

namespace
{

/*---------------------------------------------------------------------------------------------------------------------+
| local functions
+---------------------------------------------------------------------------------------------------------------------*/

void mbedTlsMutexFree(mbedtls_threading_mutex_t* const mutex)
{
	const auto ret = distortos_Mutex_destruct(mutex);
	assert(ret == 0);
}

int mbedTlsMutexLock(mbedtls_threading_mutex_t* const mutex)
{
	const auto ret = distortos_Mutex_lock(mutex);
	assert(ret == 0);
	return {};
}

void mbedTlsMutexInit(mbedtls_threading_mutex_t* const mutex)
{
	const auto ret = distortos_Mutex_construct_1p(mutex, distortos_Mutex_Protocol_priorityInheritance);
	assert(ret == 0);
}

int mbedTlsMutexUnlock(mbedtls_threading_mutex_t* const mutex)
{
	const auto ret = distortos_Mutex_unlock(mutex);
	assert(ret == 0);
	return {};
}

/*---------------------------------------------------------------------------------------------------------------------+
| local objects
+---------------------------------------------------------------------------------------------------------------------*/

/**
 * \brief Low-level initializer for mbed TLS threading
 */

BIND_LOW_LEVEL_INITIALIZER(69,
		[]()
		{
			mbedtls_threading_set_alt(mbedTlsMutexInit, mbedTlsMutexFree, mbedTlsMutexLock, mbedTlsMutexUnlock);
		});

}	// namespace
