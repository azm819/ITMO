#!/usr/bin/perl
use strict;
use warnings FATAL => 'all';

while (<>) {
    s/\b(?<f>(\w)*)(?<s>(\W)*)(?<t>(\w)*)\b/$+{t}$+{s}$+{f}/;
    print;
}