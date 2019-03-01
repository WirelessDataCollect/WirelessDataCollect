#ifndef __PLATFORM_SPECIFIC_H_
#define __PLATFORM_SPECIFIC_H_
#include "rsi_global.h"
#ifdef SPI_INTERFACE
#include "rsi_spi_cmd.h"
#endif
#include "rsi_nic.h"
#include "rsi_linux.h"

#define RSI_DPRINT(lvl, fmt, args...)              if (lvl & RSI_DEBUG_LVL) printk(fmt, ##args)

int spi_write_and_read(UINT8 *txbuf, UINT8 *rxbuf,UINT32 rx_tx_length);
int16 rsi_irqstatus(void);
INT16 rsi_read_packet(rsi_uCmdRsp *uCmdRspFrame);
int16 rsi_checkBufferFullIrq(void);
INT16 rsi_spi_iface_init(void);
void  rsi_ulp_wakeup_init(void);

#ifndef NULL
#define NULL 0
#endif
#endif
