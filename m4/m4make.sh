#!/bin/sh
# Invoke m4 on a Makefile, and write the contents into
# a temporary file, which is invoked by make.
# Any arguments passed to this are passed into Make.

if [[ "$1" == "--help" || "$1" == "-h" ]]; then
    echo 'm4make - utility to invoke m4 on a makefile and execute it'
    echo 'usage: m4make [--help | -h] [...]'

    exit 0
fi

makefile_path=`pwd`/Makefile
dummy_makefile=`pwd`/_Makefile

if [[ -f "$dummy_makefile" ]]; then
    rm "$dummy_makefile"
fi

if [[ ! -f "$makefile_path" ]]; then
    echo 'm4make: error, could not find makefile. exiting'
    
    exit 1
fi

m4 "$makefile_path" > "$dummy_makefile"
make --makefile "$dummy_makefile" $@

rm "$dummy_makefile"
