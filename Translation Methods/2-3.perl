#!/usr/bin/perl
use strict;
use warnings FATAL => 'all';

while (<>) {
    s/\b(a|A)+\b/argh/;
    print;
}