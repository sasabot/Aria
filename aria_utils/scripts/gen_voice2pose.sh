#!/bin/bash
if [ -f "$1" ]
then
    echo "$1 exists"
else
    body=''

    for entry in ../motions/*.py
    do
	tmp="${entry##*/}"
	body="${body}${tmp:0:${#tmp}-3}:\n"
    done

    echo -e $body > $1
fi