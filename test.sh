#!/usr/bin/bash
./pbuild "x+2x^2" p1
./pview p1
./pbuild "-2x^2-2" p2
./pview p2
./psum p1 p2 soma
./psub p1 p2 sub
./pview soma
./pview sub
