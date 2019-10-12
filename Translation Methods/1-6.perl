#!/usr/bin/perl
use strict;
use warnings FATAL => 'all';

while (<>) {
    print if /^(((\w)*(\W)*)*(\W))*(\d){1,}((\W)((\w)*(\W)*)*)*$/;
}