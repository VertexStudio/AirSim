#!/usr/bin/env bash

pushd ../build_debug/output/bin

./AutoAgent Drone00 &
A1=$!
./AutoAgent Drone01 &
A2=$!
./AutoAgent Drone02 &
A3=$!
./AutoAgent Drone03 &
A4=$!
./AutoAgent Drone10 &
A5=$!
./AutoAgent Drone11 &
A6=$!
./AutoAgent Drone12 &
A7=$!
./AutoAgent Drone13 &
A8=$!
./AutoAgent Drone20 &
A9=$!
./AutoAgent Drone21 &
A10=$!
./AutoAgent Drone22 &
A11=$!
./AutoAgent Drone23 &
A12=$!
./AutoAgent Drone30 &
A13=$!
./AutoAgent Drone31 &
A14=$!
./AutoAgent Drone32 &
A15=$!
./AutoAgent Drone33 &
A16=$!
./AutoAgent Drone40 &
A17=$!
./AutoAgent Drone41 &
A18=$!
./AutoAgent Drone42 &
A19=$!
./AutoAgent Drone43 &
A20=$!
./AutoAgent Drone50 &
A21=$!
./AutoAgent Drone51 &
A22=$!
./AutoAgent Drone52 &
A23=$!
./AutoAgent Drone53 &
A24=$!
./AutoAgent Drone60 &
A25=$!

wait $A1 $A2 $A3 $A4 $A5 $A6 $A7 $A8 $A9 $A10 $A11 $A12 $A13 $A14 $A15 $A16 $A17 $A18 $A19 $A20 $A21 $A22 $A23 $A24 $A25
