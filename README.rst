=================================
FogLAMP "Threshold" Filter plugin
=================================

A filter that applies a threshold function to the data stream and only
passes data when this expression evaluates to true.

If an asset, or dat astream in the case of a north task, has other data
points or assets that are not part of the expression, then they too are
subject to the threshold. If the expression evalues to false then no
assets will be forwarded on that stream. This allows a single value to
control the forwarding of data.

Any example use might be to have two north streams, one that uses a high
cost, link to send data when soem condition that requires close montirign
occurs and the othe rthat is used to send data by a lower cost mechanism
when normal operating conditions apply.

E.g. We have a temperature critical process, when the temperature is
above 80 degrees it most be closely monutored. We use a high cost link
to send data north wards in this case. We woudl have a north task setup
that has the threshold filter with the condition:

  temperature >= 80

We then have a second, lower cost link with a north task using the
threshold filter with the condition:

  temperature < 80

This way all data is sent once, but data is sent in an expediated fashion
if the temperature is above the 80 degreee threshold.

Configuration
-------------

The filter supports the following set of configuration options

expression
  The threshold function to apply


Build
-----
To build FogLAMP "Threshold" filter plugin:

.. code-block:: console

  $ mkdir build
  $ cd build
  $ cmake ..
  $ make

- By default the FogLAMP develop package header files and libraries
  are expected to be located in /usr/include/foglamp and /usr/lib/foglamp
- If **FOGLAMP_ROOT** env var is set and no -D options are set,
  the header files and libraries paths are pulled from the ones under the
  FOGLAMP_ROOT directory.
  Please note that you must first run 'make' in the FOGLAMP_ROOT directory.

You may also pass one or more of the following options to cmake to override 
this default behaviour:

- **FOGLAMP_SRC** sets the path of a FogLAMP source tree
- **FOGLAMP_INCLUDE** sets the path to FogLAMP header files
- **FOGLAMP_LIB sets** the path to FogLAMP libraries
- **FOGLAMP_INSTALL** sets the installation path of Random plugin

NOTE:
 - The **FOGLAMP_INCLUDE** option should point to a location where all the FogLAMP 
   header files have been installed in a single directory.
 - The **FOGLAMP_LIB** option should point to a location where all the FogLAMP
   libraries have been installed in a single directory.
 - 'make install' target is defined only when **FOGLAMP_INSTALL** is set

Examples:

- no options

  $ cmake ..

- no options and FOGLAMP_ROOT set

  $ export FOGLAMP_ROOT=/some_foglamp_setup

  $ cmake ..

- set FOGLAMP_SRC

  $ cmake -DFOGLAMP_SRC=/home/source/develop/FogLAMP  ..

- set FOGLAMP_INCLUDE

  $ cmake -DFOGLAMP_INCLUDE=/dev-package/include ..
- set FOGLAMP_LIB

  $ cmake -DFOGLAMP_LIB=/home/dev/package/lib ..
- set FOGLAMP_INSTALL

  $ cmake -DFOGLAMP_INSTALL=/home/source/develop/FogLAMP ..

  $ cmake -DFOGLAMP_INSTALL=/usr/local/foglamp ..
