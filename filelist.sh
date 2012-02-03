#!/bin/bash
strace_out=$(tempfile)

function die()
{
	echo "$*" >&2
	rm -f "${strace_out}"
	exit 1
}

make clean

strace -f -o"${strace_out}" make >/dev/null 2>&1 || die "unable to build"
cat "${strace_out}" | fgrep 'open(' | fgrep FFmpeg/ | fgrep -v build | fgrep -v ' = -1' | awk -F'"' '{print $2;}' | sort -u
rm -f "${strace_out}"
