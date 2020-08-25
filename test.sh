#!/bin/bash

if cmake -B./build -H./
then
  if make --directory build
  then
    make --directory build test
   
    # Run specific case. 
    # ./build/src/fdc-cli './dataset/Complete Data/adult.json'
  fi
fi


