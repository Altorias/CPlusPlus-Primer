#!/bin/bash

rm close_server
cd ../bin
nohup ./LRUServer > ../log/output.log 2>&1 &
