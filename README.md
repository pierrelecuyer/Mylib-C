# mylib
A Small Collection of Old Basic Utilities in C

### COMPILATION of the Package:

- Before compiling the package, you may have to set some global constants 
  in file mylib/gdef.tex to their appropriate values if the default values
  are not accepted by your platform (the mylib/gdef.h will be created
  automatically).

- All the header files (*.h) of the package will be created automatically 
  from the corresponding *.tex files when building the package libraries.

- 1) Call
	autoreconf -fvi
  to produce configure scripts.
 
- 2) Call configure (or sh ./configure) to configure the package for your system.
  Give also the name of the directory where you want to install the libraries
  and binaries. It is advised to set the install directory completely 
  separate from the package directory.
  
	 ./configure --prefix= &lt;install directory> --disable-shared

  For example, if you want to install it in the directory usr in the
  user's home directory, call (directory usr MUST EXIST)
	 ./configure --prefix=$HOME/usr --disable-shared

  If no prefix is given in the configure command above, then the libraries
  will be installed in the standard directory /usr/local, but only the
  system administrator has the permissions to do that.

- 3) Call
	make
  to compile everything and build the libraries.

- 4) Call
	make install
  to install the libraries in the chosen directory.
