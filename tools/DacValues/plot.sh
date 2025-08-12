#!/bin/bash

CMD_BEGIN="set y2tics; set ytics nomirror; set y2tics nomirror;"

CMD_END+=";pause -1"

gnuplot -e "$CMD_BEGIN $@ $CMD_END"
