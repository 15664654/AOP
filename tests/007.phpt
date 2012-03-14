--TEST--
Exception
--FILE--
<?php 

class mytest {
	public $data = "";
	public function test () {
		return "test-".$this->data;
	}
}

AOP_add("mytest::test", function ($pObj) {return "around".$pObj->process();});
$test = new mytest();
$test->data="prop";
echo $test->test();

?>
--EXPECT--
aroundtest-prop