#!/usr/bin/perl
use strict;
use warnings FATAL => 'all';

while (<>) {
    print if /cat|caT|cAt|cAT|Cat|CaT|CAt|CAT/;
}