#!/usr/bin/perl
$empty = 0;
$str = 0;
while (<>) {
    if (/^(\s)*$/) {
        $empty = 1;
    } else {
        s/(\s)+/$1/g; # replace double spaces
        if (/^(\s)*(?<f>((\S)+\s*?)*)(\s)*$/){ # mark text which is surrounded by spaces as {f}
            if ($str == 1 && $empty == 1) {
                print "\n";
            }
            print $ + {f}; # print text
            print "\n";
            $empty = 0;
            $str = 1;
        }
    }
}