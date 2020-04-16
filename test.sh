#!/bin/bash

cmake -B./build -H./

make --directory build test

