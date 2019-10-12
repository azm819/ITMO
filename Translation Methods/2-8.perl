#!/usr/bin/perl
use strict;
use warnings FATAL => 'all';

while (<>) {
    s/\b(?<f>(\d)*)(0)\b/$+{f}/g;
    print;
}