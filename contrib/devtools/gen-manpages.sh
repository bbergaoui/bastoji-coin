#!/usr/bin/env bash

export LC_ALL=C
TOPDIR=${TOPDIR:-$(git rev-parse --show-toplevel)}
BUILDDIR=${BUILDDIR:-$TOPDIR}

BINDIR=${BINDIR:-$BUILDDIR/src}
MANDIR=${MANDIR:-$TOPDIR/doc/man}

BASTOJID=${BASTOJID:-$BINDIR/bastojid}
BASTOJICLI=${BASTOJICLI:-$BINDIR/bastoji-cli}
BASTOJITX=${BASTOJITX:-$BINDIR/bastoji-tx}
BASTOJIQT=${BASTOJIQT:-$BINDIR/qt/bastoji-qt}

[ ! -x $BASTOJID ] && echo "$BASTOJID not found or not executable." && exit 1

# The autodetected version git tag can screw up manpage output a little bit
BTJVER=($($BASTOJICLI --version | head -n1 | awk -F'[ -]' '{ print $6, $7 }'))

# Create a footer file with copyright content.
# This gets autodetected fine for bastojid if --version-string is not set,
# but has different outcomes for bastoji-qt and bastoji-cli.
echo "[COPYRIGHT]" > footer.h2m
$BASTOJID --version | sed -n '1!p' >> footer.h2m

for cmd in $BASTOJID $BASTOJICLI $BASTOJITX $BASTOJIQT; do
  cmdname="${cmd##*/}"
  help2man -N --version-string=${BTJVER[0]} --include=footer.h2m -o ${MANDIR}/${cmdname}.1 ${cmd}
  sed -i "s/\\\-${BTJVER[1]}//g" ${MANDIR}/${cmdname}.1
done

rm -f footer.h2m
