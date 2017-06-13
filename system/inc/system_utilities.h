/**
 ******************************************************************************
  Copyright (c) 2013-2014 IntoRobot Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation, either
  version 3 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, see <http://www.gnu.org/licenses/>.
  ******************************************************************************
*/

#ifndef SYSTEM_UTILITIES_H_
#define SYSTEM_UTILITIES_H_

#include <stdint.h>
#include "params_hal.h"
#include "system_product.h"

#ifdef __cplusplus
extern "C" {
#endif

int system_version(char *pversion);
int system_platform_id(char *pid);
int system_platform_name(char *pname);
AT_MODE_FLAG_TypeDef system_security_mode(void);
product_mode_t system_product_mode(void);

#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_UTILITIES_H_ */
