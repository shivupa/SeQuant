#!/bin/bash

cmake -B build -S . -G Ninja -DSEQUANT_BUILD_DOCS=ON
