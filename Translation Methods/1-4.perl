#!/usr/bin/perl
use strict;
use warnings FATAL => 'all';

while (<>) {
    print if /z((\w)|(\W))((\w)|(\W))((\w)|(\W))z/;
}