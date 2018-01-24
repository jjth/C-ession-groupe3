#!/bin/bash
killall Pair > /dev/null
killall Impair > /dev/null
sleep 2

cd build/pair
./Pair &
cd ../impair
./Impair &
cd ..
./Central

