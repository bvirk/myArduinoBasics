#### Reference

[Doxygen](http://www.doxygen.nl/manual/)


#### Selected style

Only style elements that makes documentation in readable in source is preferred - in other words: it must not be clumsy in source because of use of special \whatever commands. Markdown is OK

The Qt style is prefered over java or c++


//! Foo short description  
/*! On one line detailed description */ 
class Foo {


//! Foo short description  
/*! 
  Multible lines description
  about a class
  which name is Foo
*/
class Foo {

//! function or public methods foo short description  
/*!
  Detailed description spans multible 
  lines. The three item this adresses is:
  
  1. global functions
  2. namespaced functions
  3. methods
  \param parameter is explained
  \return type is explained
*/
int foo(int parameter)

1. list et
2. list to 
3. list tre


int variable; //!< Brief description after the member 

//! An enum.
/*! More detailed enum description. */
enum TEnum { 
