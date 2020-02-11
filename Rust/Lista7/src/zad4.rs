fn gen_sequence(n: i32) -> (Vec<i32>, Vec<i32>) {
    let mut john = Vec::new();
    let mut ann = Vec::new();
    john.push(0);
    ann.push(1);
    for i in 1..n {
        john.push(i as i32 - ann[john[i as usize - 1] as usize]);
        ann.push(i as i32 - john[ann[i as usize - 1] as usize]);
    }
    (ann, john)
}

fn john(n: i32) -> Vec<i32> {
    gen_sequence(n).1
}
fn ann(n: i32) -> Vec<i32> {
    gen_sequence(n).0
}
fn sum_john(n: i32) -> i32 {
    john(n).iter().sum::<i32>()
}
fn sum_ann(n: i32) -> i32 {
    ann(n).iter().sum::<i32>()
}

fn test_john(n: i32, exp: Vec<i32>) -> () {
    assert_eq!(john(n), exp)
}
fn test_ann(n: i32, exp: Vec<i32>) -> () {
    assert_eq!(ann(n), exp)
}
fn test_sum_john(n: i32, exp: i32) -> () {
    assert_eq!(sum_john(n), exp)
}
fn test_sum_ann(n: i32, exp: i32) -> () {
    assert_eq!(sum_ann(n), exp)
}

#[test]
fn test_test_john() {
    test_john(11, vec![0, 0, 1, 2, 2, 3, 4, 4, 5, 6, 6]);
    test_john(14, vec![0, 0, 1, 2, 2, 3, 4, 4, 5, 6, 6, 7, 7, 8]);
    test_john(22, vec![0, 0, 1, 2, 2, 3, 4, 4, 5, 6, 6, 7, 7, 8, 9, 9, 10, 11, 11, 12, 12, 13]);
    test_john(38, vec![0, 0, 1, 2, 2, 3, 4, 4, 5, 6, 6, 7, 7, 8, 9, 9, 10, 11, 11, 12, 12, 13, 14, 14, 15, 16, 16, 17, 17, 18, 19, 19, 20, 20, 21, 22, 22, 23]);
}
#[test]
fn test_test_ann() {
    test_ann(6, vec![1, 1, 2, 2, 3, 3]);
    test_ann(15, vec![1, 1, 2, 2, 3, 3, 4, 5, 5, 6, 6, 7, 8, 8, 9]);
    test_ann(25, vec![1, 1, 2, 2, 3, 3, 4, 5, 5, 6, 6, 7, 8, 8, 9, 9, 10, 11, 11, 12, 13, 13, 14, 14, 15]);
    test_ann(31, vec![1, 1, 2, 2, 3, 3, 4, 5, 5, 6, 6, 7, 8, 8, 9, 9, 10, 11, 11, 12, 13, 13, 14, 14, 15, 16, 16, 17, 17, 18, 19]);
}
#[test]
fn test_test_sum_john() {
    test_sum_john(75, 1720);
    test_sum_john(78, 1861);
    test_sum_john(150, 6919);
    test_sum_john(255, 20039);
}
#[test]
fn test_test_sum_ann() {
    test_sum_ann(115, 4070);
    test_sum_ann(150, 6930);
    test_sum_ann(215, 14249);
    test_sum_ann(198, 12083);
}