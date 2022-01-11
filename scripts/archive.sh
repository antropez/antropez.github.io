#!/bin/sh

# A script to traverse each project, and create gzip'd archives using the version number.
# It will also create 'user' archives for all projects ending in -dev by invoking the 
# 'conform' target of the project's Makefile.

for project in projects/*; do
    project_name=`basename $project`
    project_version=`cat $project/.VERSION`
    base_name=`echo $project_name | cut -d'-' -f 1`

    mkdir "archives/$base_name" --parents

    # Create an archive for this project
    cd projects
    tar -cvzf "$project_name-$project_version.tar.gz" "$project_name"

    # Create a conforming user installation
    if [[ "$project_name" == *-dev ]]; then
        cd $project_name

        make clean
        make conform
        cd ..
        tar -cvzf "$base_name-user-$project_version.tar.gz" "$base_name-user"
        rm -r "$base_name-user"
        cd ..
    fi

    mv projects/*.gz "archives/$base_name"
done
