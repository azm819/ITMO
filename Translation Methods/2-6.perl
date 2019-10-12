#!/usr/bin/perl
use strict;
use warnings FATAL => 'all';

while (<>) {
    s/(?<f>\w)\g1/$+{f}/g;
    print;
}