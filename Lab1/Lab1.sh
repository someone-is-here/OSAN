#!/bin/bash
echo USERNAME: $USER
echo CURRENT_TIME: $(date '+ %H:%M:%S')
echo CURRENT_DATE: $(date '+%Y-%m-%S')
echo CURRENT_DIRICTORY: $PWD
echo AMOUNT_OF_PROCESSES: $(ps aux --no-heading | wc -l) 
echo WORKING_TIME: $(uptime -p)
