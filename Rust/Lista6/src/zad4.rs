fn comp(a: Vec<i64>, b: Vec<i64>) -> bool {
    let mut a_mut: Vec<i64> = a.iter().map(|&number| number*number).collect();
    let mut b_mut: Vec<i64> = b.to_vec();
    a_mut.sort();
    b_mut.sort();
    for i in 0..a_mut.len() {
        if a_mut[i] != b_mut[i] {
            return false;
        }
    }
    a_mut.len() == b_mut.len()
}

fn testing(a: Vec<i64>, b: Vec<i64>, exp: bool) -> () {
    assert_eq!(comp(a, b), exp)
}

#[test]
fn tests_comp() {

    let a1 = vec![121, 144, 19, 161, 19, 144, 19, 11];
    let a2 = vec![11*11, 121*121, 144*144, 19*19, 161*161, 19*19, 144*144, 19*19];
    testing(a1, a2, true);
    let a1 = vec![121, 144, 19, 161, 19, 144, 19, 11];
    let a2 = vec![11*21, 121*121, 144*144, 19*19, 161*161, 19*19, 144*144, 19*19];
    testing(a1, a2, false);
    let a1 = vec![];
    let a2 = vec![];
    testing(a1, a2, true);
    let a1 = vec![1];
    let a2 = vec![1*1];
    testing(a1, a2, true);
    let a1 = vec![4];
    let a2 = vec![2*2];
    testing(a1, a2, false);
    let a1 = vec![4, 16];
    let a2 = vec![2*2, 4*4];
    testing(a1, a2, false);
    let a1 = vec![4, 4, 4, 4, 4, 4];
    let a2 = vec![2*2];
    testing(a1, a2, false);
    let a1 = vec![144, 81, 64];
    let a2 = vec![3*3, 2*2, 10*10];
    testing(a1, a2, false);
    let a1 = vec![100, 112, 125];
    let a2 = vec![5*5, 6*6, 2*2];
    testing(a1, a2, false);
    let a1 = vec![11, 12, 13, 15, 16, 18, 19, 20];
    let a2 = vec![7*7];
    testing(a1, a2, false);

}