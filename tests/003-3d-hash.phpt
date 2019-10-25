--TEST--
Check morton_(de)interleave3 function
--SKIPIF--
<?php
include 'skipif.inc';
--FILE--
<?php

$coordinates = [
	//basic tests
	[100, 200, 50],
	[100, 200, -50],
	[100, -200, 50],
	[100, -200, -50],
	[-100, 200, 50],
	[-100, 200, -50],
	[-100, -200, 50],
	[-100, -200, -50],

	[0xfffff, 0xfffff, 0xfffff], //signed int21 max
	[-0xfffff - 1, -0xfffff - 1, -0xfffff - 1], //signed int21 min
];

foreach($coordinates as $coordinate){
	list($x, $y, $z) = $coordinate;
	$hash = morton_interleave3($x, $y, $z);
	morton_deinterleave3($hash, $x1, $y1, $z1);
	$valid = $x1 === $x1 && $y === $y1 && $z === $z1;
	echo "[$x, $y, $z, $hash]" . ($valid ? "" : ": failed ($x1, $y1, $z1, $hash)") . "\n";
}
--EXPECT--
[100, 200, 50, 5162080]
[100, 200, -50, 5270498306779024736]
[100, -200, 50, 2635249153382802528]
[100, -200, -50, 7905747460156665184]
[-100, 200, 50, -7905747460156664224]
[-100, 200, -50, -2635249153382801568]
[-100, -200, 50, -5270498306779023776]
[-100, -200, -50, -5161120]
[1048575, 1048575, 1048575, 1152921504606846975]
[-1048576, -1048576, -1048576, -1152921504606846976]
