#ifndef _NIOS_SYSTEM_H_
#define _NIOS_SYSTEM_H_

#define RS232_Control   (*(volatile unsigned char *)(0x84000200))
#define RS232_Status    (*(volatile unsigned char *)(0x84000200))
#define RS232_TxData    (*(volatile unsigned char *)(0x84000202))
#define RS232_RxData    (*(volatile unsigned char *)(0x84000202))
#define RS232_Baud      (*(volatile unsigned char *)(0x84000204))

#endif /* _NIOS_SYSTEM_H_ */
