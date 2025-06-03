#!/bin/bash

timetag=$(date '+%d.%m.%Y.%H.%M.%S')
sudo git checkout stg
sudo git merge --commit dev
sudo git tag "$timetag"
sudo git push origin "$timetag"
sudo git checkout dev
sudo git commit -m "revision transfered from dev to stg"
sudo git push origin stg
