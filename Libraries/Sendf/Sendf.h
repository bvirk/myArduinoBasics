/*! \file Sendf.h
	Serial versions of standard C printf.
*/

//! Serial 'printf' for NON float or double variadic arguments. 
/*
  A fixed buffer af length 0x40 bytes is used - the formatted stream will maximal be 0x3f bytes long. Care is taken not to overflow, 
  as it is vsnprintf that is used.

  \param fmt is like the format string of printf, except %e and %f must not be used
  \param variadic arguments can not be of type float or double.
  \return length of sendt stream.
*/
int8_t sendf(const char * fmt, ...);


//! Serial 'printf' for ONLY float or double variadic arguments. 
/*
  sendff for sendf-floats.  A fixed buffer af length 0x40 bytes is used - the formatted stream will maximal be 0x3f bytes long. 
  Care is taken not to overflow, as it is vsnprintf that is used.
  Only format specifiers %[.d]e and %[.d]f in the format string will be reconized - d, the optional precision specifier, is a single 
  digit in range {0 .. 7} - a 8 or 9 means 7. Absense of precision specifier defaults it to DOUBLE_DEFAULT_PRECISION.
  A midtrange area between not big numbers and not small number will, on request using %f, be sendt in normal decimal notation - 
  outside that range the format is switched to scientific notation. The switching occurs when:
  
  	abs(number) > 9999999*pow(10,-precision) or abs(number) < pow(10,precision-8) as presision is in range {0 .. 7} 
  
  In that way it is adequate, given no higher precision than 7, to offer dtostre or dtostrf a 0xf bytes buffer.  

  \param fmt is like the format string of printf, except only %e and %f format specifiers must be used.
  \param variadic arguments can only be of type float or double.
  \return length of sendt stream.
*/
int8_t sendff(const char * fmt, ...);


//! convert, in scientific notation, float or double to char *
/*
  This an overload of stdlib char * dtostre(... using a dedicated buffer and leading + chosen as space before the scientific
  notation number
  
  \param d is double (or float) to be converted to char buffer
  \param prec is precision which is limited to 7.
  \return char buffer of converted value
*/
inline char * dtostre(double d, uint8_t prec);


//! convert, in decimal notation, float or double to char *
/*
  This an overload of stdlib char * dtostrf(... using a dedicated buffer and a width parameter which is 0. Care must to taken
  not to overflow the buffer - the used buffer only has room for 14 bytes! See doc for function sendff 
  
  \param d is double (or float) to be converted to char buffer
  \param prec is precision which is limited to 7.
  \return char buffer of converted value
*/
inline char * dtostrf(double d, uint8_t prec);
