#!/bin/bash

mv $1 ../darknet-master
cd ..
cd darknet-master
path=$1
./darknet detector test obj.data yolo-obj.cfg yolo-obj_best.weights -ext_output ${path} >> ${path}.txt
mv predictions.jpg ${path}.jpg
