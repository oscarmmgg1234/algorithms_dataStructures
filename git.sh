#!/usr/bin/env bash

#Input for commit title 
read -p 'Commit Message: ' COMMIT

#git commit 
git add .
git commit -m "$COMMIT"
git push origin master

echo 'Script Done Boiii'