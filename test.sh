#!/bin/bash

cmake -B./build -H./

make --directory build

make --directory build test


