#!/bin/bash

if cmake -B./build -H./
then
  if make --directory build
  then
    make --directory build test
  fi
fi


