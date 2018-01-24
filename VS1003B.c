
/*************************************************************/
/*          VS1003 diriver for  MiniMP3 Player     *               */
/*                                                                 */
/* Platform   : AVRStudio4.12 sp4 + WinAVR20060421                 */
/*              optimize -0s                                       */
/* Author     : bozai(Zhang Qibo)                                  */
/* E-mail     : sudazqb@163.com                                    */
/* MSN        : zhangqibo_1985@hotmail.com                         */
/* Date       : 2006-12-26                                         */
/*******************************************************************/
#include<avr/io.h>
#include"VS1003B.h"


//low speed
void VS1003B_SPI_Low(void)
{
	SPCR =   _BV(SPE)|_BV(MSTR);
	SPSR &= ~_BV(SPI2X);
}

//full speed
void VS1003B_SPI_High(void)
{
	SPCR =  _BV(SPE)|_BV(MSTR);
	SPSR |= _BV(SPI2X);
}

//delay
void VS1003B_Delay(uint16_t n)
{
 uint16_t j;	
	for(j=0;j<3;j++) {
	while(n--) asm("nop");
    }
}

//write one byte to vs1003
uint8_t VS1003B_WriteByte(uint8_t CH)
{   
	SPDR = CH;
	while(!(SPSR & _BV(SPIF)));
	return SPDR;
}

//read one byte from vs1003
uint8_t VS1003B_ReadByte()
{
    SPDR = 0xff;
	while(!(SPSR & _BV(SPIF)));
	return SPDR;
}

//config register
void VS1003B_WriteCMD(uint8_t addr, uint16_t dat)
{
	VS1003B_XDCS_H();
	VS1003B_XCS_L();
	VS1003B_WriteByte(0x02);
	VS1003B_WriteByte(addr);
	VS1003B_WriteByte(dat>>8);
	VS1003B_WriteByte(dat);
	VS1003B_XCS_H();
}

///read register
uint16_t VS1003B_ReadCMD(uint8_t addr)
{
	uint16_t temp;
	VS1003B_XDCS_H();
	VS1003B_XCS_L();
	VS1003B_WriteByte(0x03);
	VS1003B_WriteByte(addr);
	temp = VS1003B_ReadByte();
	temp <<= 8;
	temp += VS1003B_ReadByte();
	VS1003B_XCS_H();
	return temp;
}

//write data (music data)
void VS1003B_WriteDAT(uint8_t dat)
{
	VS1003B_XCS_H();
	VS1003B_XDCS_L();
	VS1003B_WriteByte(dat);
	VS1003B_XDCS_H();
	VS1003B_XCS_H();
}

//initialize VS1003
uint8_t VS1003B_Init()
{
	uint8_t retry;
	PORT_INI();
	DDR_INI();
	VS1003B_DDR &=~_BV(VS1003B_DREQ);
	VS1003B_XCS_H();
	VS1003B_XDCS_H();
	VS1003B_XRESET_L();
	VS1003B_Delay(0xffff);
	VS1003B_XRESET_H();//chip select
	VS1003B_SPI_Low();//low speed
	VS1003B_Delay(0xffff);//delay
	retry=0;
	while(VS1003B_ReadCMD(0x00) != 0x0800)//set mode register
	{
		VS1003B_WriteCMD(0x00,0x0800);//VS1003B_WriteCMD(0x00,0x0800);
		if(retry++ >10 )break;//{PORTB|=_BV(PB1);break;}
	}
	retry=0;
	/*
	while(VS1003B_ReadCMD(0x03) != 0xc000)//set PLL register
	{
		VS1003B_WriteCMD(0x03,0xc000); //VS1003B_WriteCMD(0x03,0xc000)
		if(retry++ >10 )break;
	}
	*/
	while(VS1003B_ReadCMD(0x03) != 0xc000)//set PLL register
	{
		VS1003B_WriteCMD(0x03,0xc000); //VS1003B_WriteCMD(0x03,0xa000)
		if(retry++ >10 )break;
	}

	retry=0;
	while(VS1003B_ReadCMD(0x0b) != DefaultVolume)//set Volume
	{
		VS1003B_WriteCMD(0x0b,DefaultVolume);
		if(retry++ >10 )break;
	}
	VS1003B_SPI_High();//turn to high speed
	VS1003B_XDCS_H();
	VS1003B_XCS_H();
	if(retry > 10)return 1;
	return 0;
}

//VS1003 soft reset
void VS1003B_SoftReset(void)
{
	VS1003B_WriteCMD(0x00,0x0804);//reset
	VS1003B_Delay(0xffff);//wait at least 1.35ms
}


