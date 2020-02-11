fn row_sum_odd_numbers(n:i64) -> i64 {
    let mut result: i64 = 0;
    let mut counter: i64 = first_number_in_row(n);
    for i in 1..=n {
        result += counter;
        counter += 2;
    }
    result
}

fn first_number_in_row(n:i64) -> i64 {
    let mut result: i64 = 1;
    let mut counter: i64 = 0;
    for i in 1..=n {
        result += counter;
        counter += 2;
    }
    result
}


#[test]
fn returns_expected() {
    assert_eq!(row_sum_odd_numbers(1), 1);
    assert_eq!(row_sum_odd_numbers(2), 8);
    assert_eq!(row_sum_odd_numbers(5), 125);
    assert_eq!(row_sum_odd_numbers(10), 1000);
    assert_eq!(row_sum_odd_numbers(11), 1331);
    assert_eq!(row_sum_odd_numbers(14), 2744);
    assert_eq!(row_sum_odd_numbers(22), 10648);
    assert_eq!(row_sum_odd_numbers(31), 29791);
    assert_eq!(row_sum_odd_numbers(40), 64000);
    assert_eq!(row_sum_odd_numbers(42), 74088);
    assert_eq!(row_sum_odd_numbers(4211), 74671645931);
}