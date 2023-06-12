=================================
Fledge "Threshold" Filter plugin
=================================

A filter that applies a threshold function to the data stream and only
passes data when this expression evaluates to true.

If an asset, or data stream in the case of a north task, has other data
points or assets that are not part of the expression, then they too are
subject to the threshold. If the expression evaluates to false then no
assets will be forwarded on that stream. This allows a single value to
control the forwarding of data.

Any example use might be to have two north streams, one that uses a high
cost, link to send data when some condition that requires close monitoring
occurs and the other that is used to send data by a lower cost mechanism
when normal operating conditions apply.

E.g. We have a temperature critical process, when the temperature is
above 80 degrees it most be closely monitored. We use a high cost link
to send data north wards in this case. We would have a north task setup
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
To build Fledge "Threshold" filter plugin:

.. code-block:: console

  $ mkdir build
  $ cd build
  $ cmake ..
  $ make

- By default the Fledge develop package header files and libraries
  are expected to be located in /usr/include/fledge and /usr/lib/fledge
- If **FLEDGE_ROOT** env var is set and no -D options are set,
  the header files and libraries paths are pulled from the ones under the
  FLEDGE_ROOT directory.
  Please note that you must first run 'make' in the FLEDGE_ROOT directory.

You may also pass one or more of the following options to cmake to override 
this default behaviour:

- **FLEDGE_SRC** sets the path of a Fledge source tree
- **FLEDGE_INCLUDE** sets the path to Fledge header files
- **FLEDGE_LIB sets** the path to Fledge libraries
- **FLEDGE_INSTALL** sets the installation path of Random plugin

NOTE:
 - The **FLEDGE_INCLUDE** option should point to a location where all the Fledge 
   header files have been installed in a single directory.
 - The **FLEDGE_LIB** option should point to a location where all the Fledge
   libraries have been installed in a single directory.
 - 'make install' target is defined only when **FLEDGE_INSTALL** is set

Examples:

- no options

  $ cmake ..

- no options and FLEDGE_ROOT set

  $ export FLEDGE_ROOT=/some_fledge_setup

  $ cmake ..

- set FLEDGE_SRC

  $ cmake -DFLEDGE_SRC=/home/source/develop/Fledge  ..

- set FLEDGE_INCLUDE

  $ cmake -DFLEDGE_INCLUDE=/dev-package/include ..
- set FLEDGE_LIB

  $ cmake -DFLEDGE_LIB=/home/dev/package/lib ..
- set FLEDGE_INSTALL

  $ cmake -DFLEDGE_INSTALL=/home/source/develop/Fledge ..

  $ cmake -DFLEDGE_INSTALL=/usr/local/fledge ..
