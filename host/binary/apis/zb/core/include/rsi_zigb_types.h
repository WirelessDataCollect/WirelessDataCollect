/**
 *   @file     rsi_zigb_types.h
 *   @version  1.0
 *   @date     2014-Aug-23
 *
 *   Copyright(C) Redpine Signals 2014
 *   All rights reserved by Redpine Signals.
 *
 *   @section License
 *   This program should be used on your own responsibility.
 *   Redpine Signals assumes no responsibility for any losses
 *   incurred by customers or third parties arising from the use of this file.
 *
 *   @brief API: Definitions of various data structures and variables
 *
 *   @section Description
 *   This file contains general data types 
 *
 *   @section Improvements
 *
 */


/**
 * Includes
 * */

#ifndef __RSI_ZIGB_TYPES_H
#define __RSI_ZIGB_TYPES_H

#include "rsi_common_types.h"
#ifdef LINUX_PLATFORM
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
#else
#include "stdint.h"

typedef uint16_t profile_id_t;
typedef uint16_t cluster_id_t;
typedef uint16_t ProfileID;
typedef uint16_t ClusterID;
typedef uint16_t GroupID;
#endif

#endif

