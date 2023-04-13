#!/usr/bin/perl

use strict;
use warnings;
use CGI qw(:standard);

my $count = 0;

print header,
      start_html('Perl Button Counter'),
      h1('Perl Button Counter'),
      p("Count: $count"),
      button({-onClick => 'location.href=location.href'}, 'Click me!'),
      end_html;

if (param()) {
    $count++;
}