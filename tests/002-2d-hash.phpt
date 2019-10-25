--TEST--
Check morton_(de)interleave2 function
--SKIPIF--
<?php
include 'skipif.inc';
--FILE--
<?php

$coordinates = [
	//basic tests
	[100, 200],
	[100, -200],
	[-100, 200],
	[-100, -200],

	[0x7fffffff, 0x7fffffff], //signed int32 max
	[-0x7fffffff - 1, -0x7fffffff - 1], //signed int32 min
];

foreach($coordinates as $coordinate){
	list($x, $y) = $coordinate;
	$hash = morton_interleave2($x, $y);
	morton_deinterleave2($hash, $x1, $y1);
	$valid = $x1 === $x1 && $y === $y1;
	echo "[$x, $y, $hash]" . ($valid ? "" : ": failed ($x1, $y1, $hash)") . "\n";
}
--EXPECT--
[100, 200, 46224]
[100, -200, -6148914691236553072]
[-100, 200, 6148914691236553168]
[-100, -200, -46128]
[2147483647, 2147483647, 4611686018427387903]
[-2147483648, -2147483648, -4611686018427387904]
