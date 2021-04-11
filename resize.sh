#!/bin/sh

echo "hello"

mogrify -resize 90% -quality 100 *.JPG

echo "done."
