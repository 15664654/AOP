--TEST--
processWithArgs overload arguments call (try in the second around declared)
--FILE--
<?php 

class mytest {
	public function test ($data) {
		var_dump($data);
	}
}

AOP_add("mytest::test",function ($pObj) {echo "NOOVERLOAD\n";var_dump($pObj->getArgs());$pObj->process();});
AOP_add("mytest::test",function ($pObj) {echo "OVERLOAD\n";var_dump($pObj->getArgs());$pObj->processWithArgs(array('overload'));});

$test = new mytest();
$test->test("first");

?>
--EXPECT--
OVERLOAD
array(1) {
  [0]=>
  string(5) "first"
}
NOOVERLOAD
array(1) {
  [0]=>
  string(8) "overload"
}
string(8) "overload"
