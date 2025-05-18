## Standard Conventions

> ### Conventions
> ---
> | Prefix | Description                     |
> |--------|---------------------------------|
> | a      | Array                           |
> | b      | Boolean (int)                   |
> | c      | Character                       |
> | cb     | Count of bytes                  |
> | cr     | Color reference value           |
> | cx     | Count of x (short)              |
> | dw     | Double word (unsigned long)     |
> | f      | Flags (usually multiple bit values) |
> | fn     | Function                        |
> | g_     | Global variable                 |
> | h      | Handle                          |
> | i      | Integer                         |
> | l      | Long integer                    |
> | lp     | Long pointer                    |
> | m_     | Member variable of a class      |
> | n      | Short integer                   |
> | p      | Pointer                         |
> | s      | String                          |
> | sz     | Null-terminated string          |
> | tm     | Text metric                     |
> | u      | Unsigned integer                |
> | ul     | Unsigned long integer (ULONG)   |
> | w      | Word (unsigned short)           |
> | x, y   | x, y coordinates (short)        |


> ## Other conventions
> 
> | Convention         | Description                                |
> |--------------------|--------------------------------------------|
> | CMyClass           | Prefix 'C' for C++ class names.           |
> | COMyObjectClass    | Prefix 'CO' for COM object class names.    |
> | CFMyClassFactory   | Prefix 'CF' for COM class factory names.   |
> | IMyInterface       | Prefix 'I' for COM interface class names.  |
> | CImpIMyInterface   | Prefix 'CImpI' for COM interface implementation classes. |


## Header Comment Conventions

| Token | Description                        |
|-------|------------------------------------|
| /*+   | File Header Begin                 |
| +*/   | File Header End                   |
| /*-   | Plain comment block Header Begin  |
| -*/   | Plain comment block Header End    |
| /*C   | Class Header Begin                |
| C*/   | Class Header End                  |
| /*M   | Method Header Begin               |
| M*/   | Method Header End                 |
| /*F   | Function Header Begin             |
| F*/   | Function Header End               |
| /*I   | Interface Header Begin            |
| I*/   | Interface Header End              |
| /*O   | COM Object Class Header Begin     |
| O*/   | COM Object Class Header End       |