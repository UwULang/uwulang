#!/bin/bash
echo "Testing output:"
./uwulang test/hellOwOrld.uwu > test1.out
./uwulang test/sqwuare10000.uwu > test2.out

diff test1.out test/hello.out > diff.out
diff test2.out test/square.out >> diff.out

if [ -s diff.out ] # test if diff is empty
then
    cat diff.out # print
    exit 1 # test failed
fi