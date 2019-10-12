#!/usr/bin/perl
use strict;
use warnings FATAL => 'all';

while (<>) {
    s/\b(?<f>(\w))(?<s>(\w))(?<t>(\w)*)\b/$+{s}$+{f}$+{t}/g;
    print;
}