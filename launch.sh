#!/bin/bash
killall Pair > /dev/null
killall Impair > /dev/null
cd build/pair
./Pair &
cd ../impair
./Impair &
cd ..
./Central

