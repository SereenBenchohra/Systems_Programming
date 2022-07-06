#!/bin/bash
# Runs the Java StyleCheck program for C

java -jar ~kmammen-grader/bin/StyleCheckC.jar $@
exit $?
