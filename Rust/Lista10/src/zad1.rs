fn game(n: u64) -> Vec<u64> {
    if n % 2 == 0 {
        return [n/2 * n].to_vec();
    }
    [n * n, 2].to_vec()
}

fn testing(n: u64, exp: Vec<u64>) -> () {
    assert_eq!(game(n), exp)
}

#[test]
fn basics_game() {

    testing(204, vec![20808]);
    testing(807, vec![651249, 2]);
    testing(5014, vec![12570098]);
    testing(750001, vec![562501500001, 2]);
    testing(125, vec![15625, 2]);
    testing(3122, vec![4873442]);
    testing(211258, vec![22314971282]);
    testing(5891275, vec![34707121125625, 2]);
    testing(5876, vec![17263688]);
    testing(1985, vec![3940225, 2]);
}
