#include <stdint-gcc.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <HardwareSerial.h>
#include "Sendf.h"
#include <stdarg.h>
#include <stdio.h>
#include <math.h>

#define min(a,b) ((a)<(b)?(a):(b))

const int8_t sendf_textSize=0x3f;
char sendf_text[0x40];
char double_text[0xf];

inline int8_t sendfCommon(const char * fmt, va_list args) {
	int8_t len = min(vsnprintf(sendf_text, sendf_textSize, fmt, args), sendf_textSize);
	sendf_text[len] = '\0'; 
	Serial.print(sendf_text);
	return len;
}

int8_t sendf(const char * fmt, ...) {
	va_list args;
	va_start(args, fmt);
	int8_t len = sendfCommon(fmt,args);
	va_end(args);
	return len;
}

int8_t sendf(const __FlashStringHelper *ffmt, ...) {
	va_list args;
	va_start(args, ffmt);
	
	PGM_P p = reinterpret_cast<PGM_P>(ffmt);
	uint8_t flen = strnlen_P(p,0x40);
	char fmt[flen+1];
	strncpy_P(fmt,p,flen+1);
	fmt[flen] = '\0';
	
	int8_t len = sendfCommon(fmt,args);
	va_end(args);
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

inline int8_t sendffCommon(const char * fmt, va_list args) {
       
    const char *beg = fmt;
    const char *end = fmt;
    char *dest = sendf_text;
    int8_t precsn;

    while(*end) {
        while (*end && (precsn=typeLengthPrecision(end)) == -1)            
            end++;
        if (end > beg) { // move, not format specifier containing text 
            memmove(dest,beg,end-beg);
            if (*end == '\0')
            	*(dest+(end-beg))= '\0';
        }
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
            end += (precsn >> 3) & 6;
            beg=end;
            if (*end == '\0')
            	*dest='\0';
        }
    }
    Serial.print(sendf_text);
    return strlen(sendf_text);
}

int8_t sendff(const char * fmt, ...) {
	va_list args;
	va_start(args, fmt);
	int8_t len = sendffCommon(fmt,args);
	va_end(args);
	return len;
}

int8_t sendff(const __FlashStringHelper *ffmt, ...) {
	va_list args;
    va_start(args, ffmt);
    
   	PGM_P p = reinterpret_cast<PGM_P>(ffmt);
	uint8_t flen = strnlen_P(p,0x40);
	char fmt[flen+1];
	strncpy_P(fmt,p,flen+1);
	fmt[flen] = '\0';
    
	int8_t len = sendffCommon(fmt,args);
	va_end(args);
	return len;
}

