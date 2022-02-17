#!/bin/bash

if [ -d "./output" ]; then
  rm -r ./output
fi

mkdir output
cp ./build/SpaceWar output
cp -r ./assets output
rm -rf ./output/assets/test
cp ./HowToPlay.md output/
cp -r ./snapshot output
