#ifndef __VS1003B_H__
#define __VS1003B_H__

#define DefaultVolume   0x3636
#define VS1003B_PORT    PORTB
#define VS1003B_DDR      DDRB
#define VS1003B_PIN      PINB

#define VS1003B_XCS     PB1 //XCS
#define VS1003B_XRESET  PB6 //XRESET
#define VS1003B_DREQ    PB7 //DREQ
#define VS1003B_XDCS    PB0 //XDCS


#define PORT_INI()        VS1003B_DDR |= _BV(VS1003B_XCS)|_BV(VS1003B_XRESET)|_BV(VS1003B_XDCS)
#define DDR_INI() DDRB |= _BV(PB2)|_BV(PB3)|_BV(PB5)  //MOSI = PB3, MISO = PB4, SCK = PB5 

#define VS1003B_XCS_H()    VS1003B_PORT |=  _BV(VS1003B_XCS)
#define VS1003B_XCS_L()    VS1003B_PORT &= ~_BV(VS1003B_XCS)

#define VS1003B_XRESET_H()    VS1003B_PORT |=  _BV(VS1003B_XRESET)
#define VS1003B_XRESET_L()    VS1003B_PORT &= ~_BV(VS1003B_XRESET)

#define VS1003B_XDCS_H()    VS1003B_PORT |=  _BV(VS1003B_XDCS)
#define VS1003B_XDCS_L()    VS1003B_PORT &= ~_BV(VS1003B_XDCS)

void VS1003B_SPI_Low(void);
void VS1003B_SPI_High(void);
uint8_t VS1003B_WriteByte(uint8_t CH);
uint8_t VS1003B_ReadByte(void);
void VS1003B_WriteCMD(uint8_t addr, uint16_t dat);
uint16_t VS1003B_ReadCMD(uint8_t addr);
void VS1003B_WriteDAT(uint8_t dat);
uint8_t VS1003B_Init(void);
void VS1003B_SoftReset(void);
#endif
