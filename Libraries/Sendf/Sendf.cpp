#include "Arduino.h"
#include "Sendf.h"
#include <stdarg.h>
#include <stdio.h>

const int8_t sendf_textSize=0x3f;
char sendf_text[0x40];
char double_text[0xf];



int8_t sendf(const char * fmt, ...) {
	va_list args;
	//Serial.println("in sendf variadic");
	va_start(args, fmt);
	
	int8_t len = min(vsnprintf(sendf_text, sendf_textSize, fmt, args), sendf_textSize);
	va_end(args);
	sendf_text[len] = '\0'; 
	Serial.print(sendf_text);
	return len;
}

inline char * dtostre(double d, uint8_t prec) {
	return dtostre(d,double_text,prec > 7 ? 7 : prec,true);
}

inline char * dtostrf(double d, uint8_t prec) {
	return dtostrf(d,0,prec > 7 ? 7 : prec,double_text);
}

char * (*toStr[])(double, uint8_t) = {dtostre,dtostrf};

/**
  * First %[.d]e or &[.d]f flowing point format code
  *
  * @param fmt to be searched for %[.d]e or &[.d]f strings at start
  * @return -1 for not  %[.d]e or &[.d]f at start of fmt or else
  *	bit0-2 : precision (0-7), bit 3-4: length of (2 or 4 depend on eg. %f or %.4f), bit 5: 0=e, 1=f 
  *	scientific vs decimal number
  */
inline int8_t typeLengthPrecision(const char * fmt) {
#define DOUBLE_DEFAULT_PRECISION 2
    if (*fmt == '%')
        if (*(fmt+1) =='e' || *(fmt+1) =='f')
            return DOUBLE_DEFAULT_PRECISION |  (*(fmt+1) =='f' ? 0x50 : 0x10);
        else
            if(*(fmt+1) == '.' && (*(fmt+3) == 'e' || *(fmt+3) == 'f')) {
                char prec = *(fmt+2);
                return ( isdigit(prec) ? (prec < '8' ? int(prec-48) : 7) : DOUBLE_DEFAULT_PRECISION ) | (*(fmt+3) == 'f' ? 0x60 : 0x20);
            }
    return -1;
}

/**
  * %[.d]e or %[.d]f evaluated
  * d is a single digit precision 
  */
int8_t sendff(const char * fmt, ...) {
	va_list args;
    va_start(args, fmt);
    
    //Serial.println("sendfDoubleOnlyPermittedAsVariadic");
        
    const char *beg = fmt;
    const char *end = fmt;
    char *dest = sendf_text;
    int8_t precsn;

    while(*end) {
        while (*end && (precsn=typeLengthPrecision(end)) == -1)            
            end++;
#ifdef DEBUG_COMMANDLOOP
        Serial.print("precision=");
        Serial.println(precsn,HEX);
#endif
        if (end > beg) { // move, not format specifier containing text 
            memmove(dest,beg,end-beg);
            if (*end == '\0')
            	*(dest+(end-beg))= '\0';
        }
#ifdef DEBUG_COMMANDLOOP
        else // we was at e or f format specifier
        	Serial.println("end==beg");
#endif
        if (*end) {
            dest += end-beg;
            double d = va_arg(args,double);
            double dAbs = abs(d);
            int isFmtSpecF = precsn >> 6;
            uint8_t preci = precsn & 7;
            if (isFmtSpecF && (dAbs > 9999999*pow(10,-preci) || dAbs < pow(10,preci-8)))
            	isFmtSpecF=0;
            char *flt =  (toStr[isFmtSpecF])(d,preci);
            int fltlen = strlen(flt);
            memmove(dest,flt,fltlen);
            dest +=fltlen;
#ifdef DEBUG_COMMANDLOOP
            Serial.print("skipping ");
            Serial.println((precsn >> 3) & 6);
#endif
            end += (precsn >> 3) & 6;
            beg=end;
            if (*end == '\0')
            	*dest='\0';
        }
    }
    va_end(args);
    Serial.print(sendf_text);
    return strlen(sendf_text);
}

void hexdump(const char *p, int size) {
	sendf("Address    0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");
	char ascii[0x11];
	ascii[0x10]='\0';
	for (unsigned int lineStart = (unsigned int)p & 0xfff0; lineStart < (unsigned int)p+size; lineStart += 0x10) {
		//printHex(lineStart,8,": ");
		sendf("%.8x: ",lineStart);
		for (int8_t col=0; col < 0x10; col++) 
			if (lineStart+col < (unsigned int)p || lineStart+col >= (unsigned int)p+size) {
				sendf(" . ");
				ascii[col]='.';
			} else {
				char dumpCh = *(char *)(lineStart+col);
				sendf("%.2x ",dumpCh);
				ascii[col] = dumpCh < 0x20 ? '.' : dumpCh;
			}
		sendf(" |%s|\n",ascii);
	}
}

