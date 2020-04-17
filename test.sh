#!/bin/bash

cmake -B./build -H./

if make --directory build
then
  make --directory build test
fi



