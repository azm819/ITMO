#!/usr/bin/perl
use strict;
use warnings FATAL => 'all';

while (<>) {
    print if /^((\S)((\w)*(\W)*)*(\S)|((\S)?))$/;
}