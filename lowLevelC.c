#include <conio.h>
#include <stdio.h>

typedef unsigned int uint16_t;
typedef unsigned char uint8_t; 

/* Printer BYTEs or WORDs in C*/
void printByteHex( uint8_t dato );
void printWordeHex( uint16_t dato);
void printWordeHex2( uint16_t dato, uint8_t nbytes);
/* SetBit */
uint16_t SetBit( uint16_t dato, uint8_t nbit);
/* ClrBit */
uint16_t ClrBit( uint16_t dato, uint8_t nbit);
/* WriteBit */
uint16_t WriteBit ( uint16_t dato, uint8_t valuebit ,uint8_t nbit);
/* ReverseBits */
uint16_t ReverseBits( uint16_t dato );


int main(void){
	uint16_t dato;
	printByteHex(0xF2);
	printf("\n");
	printWordeHex(0x37FD);
	printf("\n");
	printWordeHex2(0x1231,2);
	printf("\nWriteBit: " );
	printWordeHex( WriteBit(0x12FF,0,12) );
	printf("\nReverseBit Port: ");
	printWordeHex( ReverseBits(0xFFFE) );
	return 0;
}
/* 0001 0010 0011 0100 
   0010 1100 0100 1000
*/
/* Printer BYTEs or WORDs in C*/
void printByteHex( uint8_t dato ){
	uint8_t aux = dato; 
	uint8_t mask = 0x0f; 
	aux >>= 4;
	putchar( (aux&=mask) <= 9 ? aux+'0':aux+'7' );
	putchar( (dato&=mask) <= 9 ? dato+'0':dato+'7'); 
}

void printWordeHex( uint16_t dato){
    uint16_t aux = dato, mask=0xf000; 
	uint8_t i=0, z=0;
	
	while( i < 4){
		dato &= mask;
		dato >>= 12-z;
		putchar( dato <= 9? dato+'0':dato+'7' );
		mask >>= 4;
		dato = aux;
		z = z+4;
		i++;
	} 	
}

void printWordeHex2( uint16_t dato, uint8_t nbytes){
    uint16_t aux = dato, mask=0x000f<<((nbytes-1)*4); 
	uint8_t i=0, z=0, aux2=nbytes;
	
	if( nbytes > 0 && nbytes < 5){
		while( i < nbytes){
		    
			dato &= mask;
		    dato >>= ( ((aux2-1)*4)-z );
		    putchar( dato <= 9? dato+'0':dato+'7' );
		    mask >>= 4;
		    dato = aux;
		    z = z+4;
		    i++;
		    
	   } 	
	}

}

/* SetBit */
uint16_t SetBit( uint16_t dato, uint8_t nbit){
	uint16_t mask = 0x0001, aux = dato; 
	if( nbit >= 0 && nbit <= 15){
		mask = mask<<nbit;
		aux |= mask;
		return aux; 
	}
	return 0;
}

/* ClrBit */
uint16_t ClrBit( uint16_t dato, uint8_t nbit){
	uint16_t mask = 0x0001, aux = dato; 
	if( nbit >= 0 && nbit <= 15 ){
		mask = ~(mask<<nbit);
		aux &= mask;
		return aux; 
	}
	return 0;
}

/* WriteBit */
uint16_t WriteBit ( uint16_t dato, uint8_t valuebit ,uint8_t nbit){
	uint16_t mask=0x0001, aux = dato; 
	if( valuebit >= 0 && valuebit <= 1 ){
		if( nbit >= 0 && nbit <= 15 ){
			mask = mask<<nbit; 
			if( valuebit ){ /* 1 Set Bit */
				aux |= mask;
				return aux;
			} else {        /* 0 Clr Bit */
				mask = ~(mask);
				aux &= mask;
				return aux;
			}
		}
		return 0;
	} 
	return 0;
}

/* ReverseBits or ReverseBitPort */
uint16_t ReverseBits( uint16_t dato ){
	uint16_t mask=0x0001, aux;
	uint8_t i=0; 
	for(i=0; i<16; i++){
		if( dato&mask )
		   aux |= (1<<15-i);
		else 
		   aux &= ~(1<<15-i);
		
		mask=mask<<1;
	}
	return aux;
}

