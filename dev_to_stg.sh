#!/bin/bash

timetag=$(date '+%d.%m.%Y.%H.%M.%S')
git checkout stg
git merge --commit dev
git tag "$timetag"
git push origin "$timetag"
git checkout dev
git commit -m "revision transfered from dev to stg"
git push origin stg
