#!/bin/sh
# Archive qarray project

mkdir archives/qarray --parents
cd projects/
tar -czvf "qarray-`cat qarray/.VERSION`.tar.gz" qarray
mv "qarray-`cat qarray/.VERSION`.tar.gz" ../archives/qarray
