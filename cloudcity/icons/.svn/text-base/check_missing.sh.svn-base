#!/bin/sh

while read line; do
    typ=${line%/*}
    icon=${line#*/}
    if ! grep -E ".*:.*${typ}[^,]*${icon}" alias.txt > /dev/null 2>&1 ; then
        echo $line
    fi
done < full-list.txt
