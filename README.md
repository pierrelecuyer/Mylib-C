
# mylib
A Small Set of Basic Utilities in C

This library contains some basic utility functions implemented in the 
C language, mostly around the years 1995-2000, to be used in the software developed 
in the Stochastic Simulation Laboratory, at the University of Montreal, 
under the supervision of Pierre L'Ecuyer.
Many of these tools were originally implemented earlier in the Modula-2 language,
and used in our old software to analyze and test random number generators (RNGs) back 
in the late 1980's.  They were translated to C when our old 
RNG software was converted from Modula-2 to C in the late 1990's.
Some of these functions may have counterparts in recent standard C libraries, 
but we keep them to avoid rewriting our code.
They are used in particular in the TestU01 and F2LinearGen libraries.

This library has a documention in written LaTeX.
Each module has a .tex source file and these source files are used to produce
the .pdf reference manual which is located with the source files.  
The .h files are also extracted automatically 
from these .tex source files when the library is compiled.  
This ensures that the .h files agree exactly with the headers given in 
the documentation.  Thus, compiling the library erases the old .h files 
and produces fresh ones.  This is done by the tcode program described in the 
reference manual.


Contributors:  Pierre L'Ecuyer, Richard Simard, Fran\c cois Panneton,
Francis Picard, Jean-S\'ebastien S\'en\'ecal, Simon-Olivier Laperri\`ere.


### COMPILATION of the Package:

- Before compiling the package, you may have to set some global constants 
  in file `mylib/gdef.tex` to their appropriate values if the default values
  are not accepted by your platform.  Recall that `mylib/gdef.h` will be rebuilt
  automatically at compilation.

- All the header files `.h` of the package will be rebuilt automatically 
  from the corresponding `.tex` files when building the package libraries.

1) Call

		autoreconf -fvi

	  to produce configure scripts.
 
2) Call configure (or sh ./configure) to configure the package for your system.
  Give also the name of the directory where you want to install the libraries
  and binaries. It is advised to set the install directory completely 
  separate from the package directory.
 

		./configure --prefix=<install directory> --disable-shared


	 For example, if you want to install it in the directory usr in the
  user's home directory, call (directory usr MUST EXIST)
 
		./configure --prefix=$HOME/usr --disable-shared

	  If no prefix is given in the configure command above, then the libraries
  will be installed in the standard directory /usr/local, but only the
  system administrator has the permissions to do that.

3) Call

		make

	  to compile everything and build the libraries.

4) Call

		make install
	
	  to install the libraries in the chosen directory.
