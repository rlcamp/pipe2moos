# pipe2moos / moos2pipe

This project provides a minimalist interconnect between line-oriented messages on stdin/stdout, and a single MOOS string variable, for the purpose of interfacing non-C++ code with MOOS without requiring language bindings.

ISC license to the extent applicable. Yes, this C++ code was obviously written by a C person. Constructive feedback on the internal implementation is welcome.

## Usage

In one terminal window:

    path/to/moos/bin/MOOSDB

In a second terminal window:

    ./moos2pipe rx variable

In a third terminal window:

    (echo "first message"; echo "second message") | ./pipe2moos tx variable

This example will start two MOOS apps named "rx" and "tx", and print both messages in the second window, having passed the strings through a MOOSDB variable called "variable". The pipe2moos process sends one message per line ingested on stdin, and exits cleanly upon reaching eof on stdin. The moos2pipe process prints each update of the variable to stdout, and never exits unless terminated by any of the usual signals.
