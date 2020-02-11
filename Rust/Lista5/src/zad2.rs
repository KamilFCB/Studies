use std::iter::Iterator;
use std::iter::FromIterator;

fn descending_order(x: u64) -> u64 {
    let mut chars: Vec<char> = x.to_string().chars().collect();
    chars.sort_by(|a, b| b.cmp(a));
    String::from_iter(chars).parse::<u64>().unwrap()
}

#[test]
fn returns_expected() {
    assert_eq!(descending_order(0), 0);
    assert_eq!(descending_order(1), 1);
    assert_eq!(descending_order(15), 51);
    assert_eq!(descending_order(1021), 2110);
    assert_eq!(descending_order(123456789), 987654321);
    assert_eq!(descending_order(145263), 654321);
    assert_eq!(descending_order(1254859723), 9875543221);
    assert_eq!(descending_order(2518590128510), 9885552211100);
    assert_eq!(descending_order(85731897519651), 99887765553111);
    assert_eq!(descending_order(5781650000011123899), 9988765532111100000);
}