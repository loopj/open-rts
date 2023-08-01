#!/usr/bin/env bash

rm -rf docs
find -type d -name 'build' -o -type f -name 'sdkconfig' | xargs rm -rf