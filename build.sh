#!/usr/bin/bash
gcc pbuild.c poly.c -o pbuild
gcc pview.c poly.c -o pview
gcc psum.c poly.c -o psum
gcc psub.c poly.c -o psub
mkdir src
mv pbuild.c src
mv pview.c src
mv psum.c src
mv psub.c src
mv poly.c src
mv poly.h src
rm build.sh