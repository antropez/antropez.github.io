#!/bin/sh
# Process all pages with macros that must be processed

function update_versions() {
    archives=""

    rm -f $1

    for archive in archives/$2/*; do
        version=`echo $archive | sed 's/.\{1,\}-//g' | sed 's/\.tar\.gz//g'`
        archives="${archives}$version</br>"
    done

    echo $archives
}

update_versions project-pages/m4make/m4make.html m4make
