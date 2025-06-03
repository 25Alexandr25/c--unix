#!/bin/bash

timetag=$(date '+%d.%m.%Y.%H.%M.%S')
git checkout prd
git merge --commit stg
git tag "$timetag"
git push origin "$timetag"
git checkout dev
git commit -m "revision transfered from stg to prd"
git push origin prd
