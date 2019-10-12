#!/usr/bin/perl
use strict;
use warnings FATAL => 'all';

while (<>) {
    print if /^(((\w)*(\W)*)*(\W))*(cat)((\W)((\w)*(\W)*)*)*$/;
}