fn last_digit(lst: &[u64]) -> u64 {
    if lst.len() == 0 {
        return 1;
    }
    if lst.len() == 1 {
        return lst[0] % 10;
    }
    let mut power: u64 = 0;
    let mut first: i8 = 1;
    for &number in lst.iter().rev() {
        if first == 1 {
            power = number;
            first = 0;
            continue;
        }
        if power == 0 {
            power = 1;
            continue;
        }
        let min_power = std::cmp::min(power % 4 + 4, power);
        let base = std::cmp::min(number, number % 100 + 100);
        power = base.pow(min_power as u32);

    }
    power % 10
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn basic_tests() {
        let tests = vec![
            (vec![], 1),
            (vec![0, 0], 1),
            (vec![0, 0, 0], 0),
            (vec![1, 2], 1),
            (vec![3, 4, 5], 1),
            (vec![4, 3, 6], 4),
            (vec![7, 6, 21], 1),
            (vec![12, 30, 21], 6),
            (vec![2, 2, 2, 0], 4),
            (vec![937640, 767456, 981242], 0),
            (vec![123232, 694022, 140249], 6),
            (vec![499942, 898102, 846073], 6)
        ];

        for test in tests {
            assert_eq!(last_digit(&test.0), test.1);
        }
    }
}