#!/bin/bash

parec --format=float32le --rate=96000 --channels=1 | ffmpeg -ar 96000 -r 48000 -f f32le -i - output.wav
