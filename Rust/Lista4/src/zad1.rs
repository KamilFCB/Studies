fn find_digit(num: i32, nth: i32) -> i32 {
    if nth <= 0 {
        return -1;
    }
    let num_string: String = num.abs().to_string();
    if nth <= (num_string.len() as i32) {
        return num_string.chars().rev().collect::<String>().chars().nth((nth-1) as usize).unwrap().to_digit(10).unwrap() as i32;
    }
    0
}

#[test]
fn example_test() {
    assert_eq!(find_digit(5423, 4), 5);
    assert_eq!(find_digit(320, 2), 2);
    assert_eq!(find_digit(-1879, 3), 8);
    assert_eq!(find_digit(-512, 4), 0);
    assert_eq!(find_digit(12521515, 20), 0);
    assert_eq!(find_digit(652, 0), -1);
    assert_eq!(find_digit(24125, 5), 2);
    assert_eq!(find_digit(98120, 1), 0);
    assert_eq!(find_digit(25, 2), 2);
    assert_eq!(find_digit(-28781, 5), 2);
}