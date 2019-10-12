#!/usr/bin/perl

# Полный гайд по выполнению можно найти здесь: https://github.com/DubKoldun/CT-ITMO/blob/master/TranslationMethods/Perl/3.3.perl

@vector;
while (<>) {
    if (/<\s*a.+?href\s*=\s*"((((.*?):\/\/))?((.*?:.*?@))?(?<ss>\w.*?)((:|\/).*)?)".*?>/){
        $_ = $ + {ss};
        unshift(@vector, $_);
    } else {
    }
}

$last = "";

for (sort @vector) {
    if ($_ cmp $last){
        print "$_\n";
        $last = $_;
    }
}
