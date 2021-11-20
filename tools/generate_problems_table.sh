#!/bin/sh

# WIP
find ${0} -name "*.*[h|cpp]" -print | xargs awk '/^// Problem$/{f=1; next}f==0{next}/^$/{exit}{print substr($0, 1);}'
