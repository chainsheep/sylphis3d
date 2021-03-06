/* -----------------------------------------------------------------------------
 * swig.swg
 *
 * $Header: /cvs/projects/SWIG/Lib/swig.swg,v 1.4.2.42 2002/08/08 15:29:17 beazley Exp $
 *
 * Common macro definitions for various SWIG directives.  This file is always 
 * included at the top of each input file.
 * ----------------------------------------------------------------------------- */

/* Deprecated SWIG directives */

#define %disabledoc     %warn "104:%disabledoc is deprecated"
#define %enabledoc      %warn "105:%enabledoc is deprecated"
#define %doconly        %warn "106:%doconly is deprecated"
#define %style          %warn "107:%style is deprecated" /##/
#define %localstyle     %warn "108:%localstyle is deprecated" /##/
#define %title          %warn "109:%title is deprecated" /##/
#define %section        %warn "110:%section is deprecated" /##/
#define %subsection     %warn "111:%subsection is deprecated" /##/
#define %subsubsection  %warn "112:%subsubsection is deprecated" /##/
#define %new            %warn "117:%new is deprecated. Use %newobject"
#define %text           %insert("null")

/* Code insertion directives such as %wrapper %{ ... %} */

#define %init        %insert("init")
#define %wrapper     %insert("wrapper")
#define %header      %insert("header")
#define %runtime     %insert("runtime")

/* Class extension */

#define %addmethods  %warn "113:%addmethods is now %extend" %extend

/* Access control directives */

#define %readonly    %warn "114:%readonly is deprecated. Use %immutable; " %feature("immutable");
#define %readwrite   %warn "115:%readwrite is deprecated. Use %mutable; " %feature("immutable","");

#define %immutable   %feature("immutable")
#define %mutable     %feature("immutable","")

/* Directives for callback functions */

/* Experimental */

#define %callback(x) %feature("callback") `x`;
#define %nocallback  %feature("callback","");

/* Directives for attribute functions */

#define %attributefunc(_x,_y)  %pragma(swig)   attributefunction=`_x`":"`_y`;
#define %noattributefunc       %pragma(swig)   noattributefunction;

/* %ignore directive */

#define %ignore         %rename($ignore)
#define %ignorewarn(x)  %rename("$ignore:" x)

/* Generation of default constructors/destructors */

#define %nodefault     %feature("nodefault")
#define %makedefault   %feature("nodefault","")

/* Common features */

#define %exception   %feature("except")
#define %noexception %feature("except","")
#define %newobject   %feature("new")

/* Warnings */
#define %warnfilter(...) %feature("warnfilter",`__VA_ARGS__`)

/* Default handling of certain overloaded operators */

#ifdef __cplusplus
%ignorewarn("350:operator new ignored")     operator new;
%ignorewarn("351:operator delete ignored")  operator delete;
%ignorewarn("394:operator new[] ignored")   operator new[];
%ignorewarn("395:operator delete[] ignored") operator delete[];

/* Smart pointer handling */
%rename(__deref__) operator->;

/* Define std namespace */
namespace std {
}
#endif

/* Set up the typemap for handling new return strings */

#ifdef __cplusplus
%typemap(newfree) char * "delete [] $1;";
#else
%typemap(newfree) char * "free($1);";
#endif

/* Default typemap for handling char * members */

#ifdef __cplusplus
%typemap(memberin) char * {
  if ($1) delete [] $1;
  $1 = ($1_type) (new char[strlen($input)+1]);
  strcpy((char *) $1,$input);
}
%typemap(memberin,warning="451:Setting const char * member may leak memory.") const char * {
  $1 = ($1_type) (new char[strlen($input)+1]);
  strcpy((char *) $1,$input);
}
%typemap(globalin) char * {
  if ($1) delete [] $1;
  $1 = ($1_type) (new char[strlen($input)+1]);
  strcpy((char *) $1,$input);
}
%typemap(globalin,warning="451:Setting const char * variable may leak memory.") const char * {
  $1 = ($1_type) (new char[strlen($input)+1]);
  strcpy((char *) $1,$input);
}
#else
%typemap(memberin) char * {
  if ($1) free((char*)$1);
  $1 = ($1_type) malloc(strlen($input)+1);
  strcpy((char*)$1,$input);
}
%typemap(memberin,warning="451:Setting const char * member may leak memory.") const char * {
  $1 = ($1_type) malloc(strlen($input)+1);
  strcpy((char*)$1,$input);
}
%typemap(globalin) char * {
  if ($1) free((char*)$1);
  $1 = ($1_type) malloc(strlen($input)+1);
  strcpy((char*)$1,$input);
}
%typemap(globalin,warning="451:Setting const char * variable may leak memory.") const char * {
  $1 = ($1_type) malloc(strlen($input)+1);
  strcpy((char*)$1,$input);
}

#endif

/* Character array handling */

%typemap(memberin) char [ANY] {
  if ($input) strncpy($1,$input,$1_dim0);
  else $1[0] = 0;
}

%typemap(globalin) char [ANY] {
  if ($input) strncpy($1,$input,$1_dim0);
  else $1[0] = 0;
}

/* memberin typemap for arrays.   */

%typemap(memberin) SWIGTYPE [] {
  int ii;
  $1_basetype *b = ($1_basetype *) $1;
  for (ii = 0; ii < $1_size; ii++) b[ii] = *(($1_basetype *) $input + ii);
}

%typemap(globalin) SWIGTYPE [] {
  int ii;
  $1_basetype *b = ($1_basetype *) $1;
  for (ii = 0; ii < $1_size; ii++) b[ii] = *(($1_basetype *) $input + ii);
}

/* Typemap for variable length arguments sentinel value.  Used
   by the %varargs directive. */

%typemap(ignore) SWIGTYPE *VARARGS_SENTINEL, SWIGTYPE VARARGS_SENTINEL "";


/*
 * Function/method overloading support.   This is done through typemaps,
 * but also involve a precedence level. 
 */

/* Macro for overload resolution */

#define %typecheck(_x) %typemap(typecheck, precedence=_x)

/* Macros for precedence levels */

%define SWIG_TYPECHECK_POINTER       0     %enddef
%define SWIG_TYPECHECK_VOIDPTR       10    %enddef
%define SWIG_TYPECHECK_BOOL          15    %enddef
%define SWIG_TYPECHECK_UINT8         20    %enddef
%define SWIG_TYPECHECK_INT8          25    %enddef
%define SWIG_TYPECHECK_UINT16        30    %enddef
%define SWIG_TYPECHECK_INT16         35    %enddef
%define SWIG_TYPECHECK_UINT32        40    %enddef
%define SWIG_TYPECHECK_INT32         45    %enddef
%define SWIG_TYPECHECK_UINT64        50    %enddef
%define SWIG_TYPECHECK_INT64         55    %enddef
%define SWIG_TYPECHECK_UINT128       60    %enddef
%define SWIG_TYPECHECK_INT128        65    %enddef
%define SWIG_TYPECHECK_INTEGER       70    %enddef
%define SWIG_TYPECHECK_FLOAT         80    %enddef
%define SWIG_TYPECHECK_DOUBLE        90    %enddef
%define SWIG_TYPECHECK_COMPLEX      100    %enddef
%define SWIG_TYPECHECK_UNICHAR      110    %enddef
%define SWIG_TYPECHECK_UNISTRING    120    %enddef
%define SWIG_TYPECHECK_CHAR         130    %enddef
%define SWIG_TYPECHECK_STRING       140    %enddef
%define SWIG_TYPECHECK_VECTOR       150    %enddef

/*  
 * This template wrapper is used to handle C++ objects that are passed or 
 * returned by value.   This is necessary to handle objects that define
 * no default-constructor (making it difficult for SWIG to properly declare
 * local variables).
 *
 * The wrapper is used as follows.  First consider a function like this:
 *
 *      Vector cross_product(Vector a, Vector b)
 *
 * Now, if Vector is defined as a C++ class with no default constructor, 
 * code is generated as follows:
 *
 *     Vector *wrap_cross_product(Vector *inarg1, Vector *inarg2) {
 *          SwigValueWrapper<Vector>  arg1;
 *          SwigValueWrapper<Vector>  arg2;
 *          SwigValueWrapper<Vector> result;
 *
 *          arg1 = *inarg1;
 *          arg2 = *inarg2;
 *          ...            
 *          result = cross_product(arg1,arg2);
 *          ...
 *          return new Vector(result);
 *    }
 *         
 * In the wrappers, the template SwigValueWrapper simply provides a thin
 * layer around a Vector *.  However, it does this in a way that allows
 * the object to be bound after the variable declaration (which is not possible
 * with the bare object when it lacks a default constructor).  
 *
 * An observant reader will notice that the code after the variable declarations
 * is *identical* to the code used for classes that do define default constructors.
 * Thus, this neat trick allows us to fix this special case without having to
 * make massive changes to typemaps and other parts of the SWIG code generator.
 *
 * Note: this code is not included when SWIG runs in C-mode, when classes
 * define default constructors, or when pointers and references are used.
 * SWIG tries to avoid doing this except in very special circumstances.
 *
 * Note: This solution suffers from making a large number of copies
 * of the underlying object.  However, this is needed in the interest of
 * safety and in order to cover all of the possible ways in which a value
 * might be assigned.  For example:
 *
 *       arg1 = *inarg1;       // Assignment from a pointer
 *       arg1 = Vector(1,2,3); // Assignment from a value  
 *
 * This wrapping technique was suggested by William Fulton and is henceforth
 * known as the "Fulton Transform" :-).
 */

#ifdef __cplusplus
%insert("runtime") %{
#ifdef __cplusplus
template<class T> class SwigValueWrapper {
    T *tt;
public:
    inline SwigValueWrapper() : tt(0) { }
    inline ~SwigValueWrapper() { if (tt) delete tt; } 
    inline SwigValueWrapper& operator=(const T& t) { tt = new T(t); return *this; }
    inline operator T&() const { return *tt; }
    inline T *operator&() { return tt; }
};                                                    
#endif
%}
#endif

/* Macro for setting a dynamic cast function */
%define DYNAMIC_CAST(mangle,func)
%init %{
   mangle->dcast = (swig_dycast_func) func;
%}
%enddef


