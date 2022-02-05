#!/bin/bash

if [ -d "./output" ]; then
  rm -r ./output
fi

mkdir output
cp ./build/SpaceSector output
cp -r ./assets output
rm -rf ./output/assets/test
