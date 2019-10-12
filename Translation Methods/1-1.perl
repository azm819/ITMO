#!/usr/bin/perl
use strict;
use warnings FATAL => 'all';

while (<>) {
    print if /^((\w)*(\W)*)*(cat)((\w)*(\W)*)*(cat)((\w)*(\W)*)*$/;
}