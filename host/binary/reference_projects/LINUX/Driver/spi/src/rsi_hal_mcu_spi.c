/**
 * @file     rsi_hal_mcu_spi.c
 * @version  3.3
 * @date     2013-Jan-28
 *
 * Copyright(C) Redpine Signals 2012
 * All rights reserved by Redpine Signals.
 *
 * @section License
 * This program should be used on your own responsibility.
 * Redpine Signals assumes no responsibility for any losses
 * incurred by customers or third parties arising from the use of this file.
 *
 *
 */


/**
 * Includes
 */
#include "rsi_linux.h"
#include "rsi_nic.h"
#include "rsi_global.h"
#include "rsi_common.h"
#include<linux/kernel.h>
#include <linux/device.h>

#include <linux/time.h>
#include <linux/spi/spi.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/errno.h>
#include <asm/system.h>
#include <linux/delay.h>


extern struct spi_device *spi_dev;
extern uint32 rsi_spiTimer1;
extern uint32 rsi_spiTimer2;
extern uint32 rsi_spiTimer3;


/**
 * Global Variables
 */

/*==================================================================*/
/**
 * @fn          int16 rsi_spiSend_data(uint8 *ptrBuf,uint16 bufLen,uint8 *valBuf,uint8 mode)
 * @param[in]   uint8 *ptrBuf, pointer to the buffer with the data to be sent/received
 * @param[in]   uint16 bufLen, number of bytes to send
 * @param[in]   uint8 *valBuf, pointer to the buffer where the response is stored
 * @param[in]   uint8 mode, To indicate mode 8 BIT/32 BIT.
 * @param[out]  None
 * @return      0, 0=success
 * @description This API is used to send data to the Wi-Fi module through the SPI interface.
 */
int16 rsi_spiSend_data(uint8 *ptrBuf, uint16 bufLen,uint8 *valBuf,uint8 mode)
{
  uint16 status;

#ifdef RSI_DEBUG_PRINT
  RSI_DEBUG(RSI_ZONE_SPI_DBG,"\nrsi_spiSend_data:\n");
#endif
  status = spi_write_and_read(ptrBuf, valBuf, bufLen);
  return 0;
}

/*==================================================================*/
/**
 * @fn          int16 rsi_spi_send(uint8 *ptrBuf,uint16 bufLen,uint8 *valBuf,uint8 mode)
 * @param[in]   uint8 *ptrBuf, pointer to the buffer with the data to be sent/received
 * @param[in]   uint16 bufLen, number of bytes to send
 * @param[in]   uint8 *valBuf, pointer to the buffer where the response is stored
 * @param[in]   uint8 mode, To indicate mode 8 BIT/32 BIT.
 * @param[out]  None
 * @return      0, 0=success
 * @description This API is used to send data to the Wi-Fi module through the SPI interface.
 */
int16 rsi_spi_send(uint8 *ptrBuf, uint16 bufLen,uint8 *valBuf,uint8 mode)
{
  uint16 status;
#ifdef RSI_DEBUG_PRINT
  RSI_DEBUG(RSI_ZONE_SPI_DBG,"\nrsi_spiSend:\n");
#endif
  status = spi_write_and_read(ptrBuf, valBuf, bufLen);
  return 0;
}


/*==================================================================*/
/**
 * @fn          int16 rsi_spi_recv(uint8 *ptrBuf,uint16 bufLen,uint8 mode)
 * @param[in]   uint8 *ptrBuf, pointer to the buffer with the data to be sent/received
 * @param[in]   uint16 bufLen, number of bytes to send
 * @param[in]   uint8 mode, To indicate the mode 8 BIT / 32 BIT.
 * @param[out]  None
 * @return      0, 0=success
 * @description This API is used to receive data from Wi-Fi module through the SPI interface.
 */
int16 rsi_spi_recv(uint8 *ptrBuf, uint16 bufLen, uint8 mode)
{
  uint16 status;
  uint8 valBuf[1600] = {0};
  uint8 i=0;
#ifdef RSI_DEBUG_PRINT
  RSI_DEBUG(RSI_ZONE_SPI_DBG,"\nrsi_spiRecv:\n");
#endif
  status = spi_write_and_read(valBuf, ptrBuf, bufLen);
  return 0;
}

/*==================================================================*/
/**
 * @fn    int spi_write_and_read(UINT8 *txbuf, UINT8 *rxbuf, UINT32 rx_tx_length)
 * @param[in]  uint8 *txbuf, pointer to buffer with the data to be sent/received
 * @param[in]  uint8 *rxbuf, pointer to buffer with the data to be sent/received
 * @param[in]  uint32 rx_tx_length, number of bytes to send/receive
 * @param[out]  number of bytes to be written/read
 */

int spi_write_and_read(UINT8 *txbuf, UINT8 *rxbuf, UINT32 rx_tx_length)
{
  int                     status;
  struct spi_message      message;
  struct spi_transfer     t;
  uint8                   i=0;
  /* Use preallocated DMA-safe buffer.  We can't avoid copying here,
   * (as a pure convenience thing), but we can keep heap costs
   * out of the hot path ...
   */

#ifdef RSI_DEBUG_PRINT
  RSI_DEBUG(RSI_ZONE_SPI_DBG,"\nspi_write_and_read:\n");
#endif
#ifdef RSI_DEBUG_PRINTS
  RSI_DEBUG(RSI_ZONE_SPI_DBG,"Func Entry __func__ is %s \n",__func__);
#endif
#define RSI_SPI_BUFSIZ 6000
  if (rx_tx_length > RSI_SPI_BUFSIZ)
    return -EINVAL;
#ifdef RSI_DEBUG_PRINT
  RSI_DEBUG(RSI_ZONE_SPI_DBG,"\t ** Txbuf **");
  for ( i=0; i<((rx_tx_length < 16) ? (rx_tx_length) : (16)); i++)      {
    RSI_DEBUG(RSI_ZONE_SPI_DBG," %2x ",txbuf[i]);
  }
  RSI_DEBUG(RSI_ZONE_SPI_DBG,"\n");
#endif
  spi_message_init(&message);
  memset((VOID *)&t, 0, sizeof t);
  t.tx_buf = txbuf;
  t.rx_buf = rxbuf;

  t.len = rx_tx_length;
  spi_message_add_tail(&t, &message);
  status = spi_sync(spi_dev, &message);

#ifdef RSI_DEBUG_PRINT
  RSI_DEBUG(RSI_ZONE_SPI_DBG,"\t ** Rxbuf **");
  for ( i=0; i<((rx_tx_length < 16) ? (rx_tx_length) : (16)); i++)      {
    RSI_DEBUG(RSI_ZONE_SPI_DBG," %2x ",rxbuf[i]);
  }
  RSI_DEBUG(RSI_ZONE_SPI_DBG,"\n");
#endif

  if (status == 0)
  {
    status = message.status;
  }

#ifdef RSI_DEBUG_PRINT
  RSI_DEBUG(RSI_ZONE_SPI_DBG,"status is %d\n",status);
  RSI_DEBUG(RSI_ZONE_SPI_DBG," func exit %s\n",__func__);
#endif
  return status;
}

/*==============================================*/
/**
 * @fn          RSI_STATIC irqreturn_t rsi_ssp_interrupt
 *              (INT32 irq, PVOID dev_instance, struct pt_regs *regs)
 * @brief       This function is called whenever an interrupt occurs
 * @param[in]   irq, pointer to SSP inso structure
 * @param[in]   dev_instance, net_device structure instance pointer
 * @param[in]   regs
 * @param[out]  none
 * @return      Returns the status of the interrupt
 * @section description
 * This function is called whenever an interrupt occurs
 */
irqreturn_t
rsi_ssp_interrupt
(
  INT32 irq,
  PVOID dev_instance,
  struct pt_regs *regs
  )
{

#ifdef RSI_DEBUG_PRINT
  RSI_DEBUG(RSI_ZONE_SPI_DBG,"\nrsi_ssp_interrupt:\n");
#endif

  struct net_device *dev = (struct net_device *)dev_instance;
  PRSI_ADAPTER Adapter   = rsi_getpriv(dev);
  //schedule_work(&Adapter->handler);
  queue_work(Adapter->workqueue, &Adapter->handler);
#ifdef RSI_DEBUG_PRINT
    RSI_DEBUG(RSI_ZONE_INIT,"rsi_ssp_interrupt: Interrupt Handler called\n");
#endif
    return IRQ_HANDLED;
}


/*===================================================*/
/**
 * @fn          UINT8 rsi_checkBufferFullIrq(void)
 * @brief       Returns the status of the Tx buffer full interrupt flag
 * @param[in]   none
 * @param[out]  none
 * @return      uint8 rsi_strIntStatus.bufferFull
 * @section description
 * This API is used to read the status of the Buffer Full event.
 * If the buffer full event is set then the application should not send
 * any packet/command to the module until it is cleared.
 */
int16 rsi_checkBufferFullIrq(uint8 *temp)
{
#ifdef RSI_DEBUG_PRINT
  RSI_DEBUG(RSI_ZONE_SPI_DBG,"\nrsi_checkBufferFullIrq:\n");
#endif
  return rsi_device_interrupt_status(temp);
}
