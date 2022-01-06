# Create archives of each project, and add it to that project's version list.

function make_archive() {
    filename="$1-`cat projects/$1/.VERSION`.tar.gz"

    mkdir --parents archives/$1
    cd projects
    echo "Making archive of m4make: '$filename'"
    tar -cvzf "$filename" "$1"
    mv "$filename" ../archives/$1
}

make_archive "m4make"
