#!/bin/zsh

# Flag variables
FAST_RUN=false

# Parse options and arguments
while getopts ":f" opt; do
  case ${opt} in
    f ) 
      FAST_RUN=true
      ;;
    \? ) 
      echo "Invalid option: -$OPTARG" 1>&2
      exit 1
      ;;
  esac
done
shift $((OPTIND -1))

# The remaining arguments after options
ARGUMENT=$1

# Check for -fast_run flag
if [ "$FAST_RUN" = true ]; then
    g++ -std=c++17  -Wall -Wextra -Wno-sign-conversion -Wshadow -ggdb3  -DDBG -O3 -o $1 $1.cpp
else
    g++ -std=c++17 -fsanitize=address -fsanitize=undefined -Wall -Wextra -Wno-sign-conversion -Wshadow -ggdb3 -D_GLIBCXX_DEBUG -D_GLIBCXX_ASSERTIONS -ferror-limit=2 -g -DDBG -O0 -o $1 $1.cpp
fi