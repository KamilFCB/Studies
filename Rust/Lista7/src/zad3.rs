fn fcn(n: i32) -> i64 {
    (2 as i64).pow(n as u32) as i64
}

fn testequal(n: i32, exp: i64) -> () {
    assert_eq!(exp, fcn(n))
}
#[test]
fn basics() {
    testequal(17, 131072);
    testequal(21, 2097152);
    testequal(12, 4096);
    testequal(10, 1024);
    testequal(32, 4294967296);
    testequal(25, 33554432);
    testequal(42, 4398046511104);
    testequal(58, 288230376151711744);
    testequal(62, 4611686018427387904);
    testequal(35, 34359738368);
}