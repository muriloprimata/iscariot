#!/bin/sh
# Fail if olddefconfig silently dropped any option we asked for.
cd "$(dirname "$0")/.."
CFG=$(ls out/kernel-build/linux-*/.config | tail -1)
missing=0
for opt in $(grep -E '^CONFIG_[A-Z0-9_]+=y' kernel/iscariot.config | cut -d= -f1); do
grep -q "^$opt=y" "$CFG" || { echo "MISSING: $opt"; missing=1; }
done
[ "$missing" = 0 ] && echo "all requested options are set"
exit $missing
