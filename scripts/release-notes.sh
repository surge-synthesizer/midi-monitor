#!/bin/bash

cat <<- EOH
# Automatically generated Surge Midi Monitor release

This release is automatically generated every time we push Surge
Midi Monitor to main.

The build date and most recent commits are:

EOH
date
echo ""
echo "Most recent commits:" 
echo ""
git log --pretty=oneline | head -5
