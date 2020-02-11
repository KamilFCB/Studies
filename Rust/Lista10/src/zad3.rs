fn good_vs_evil(good: &str, evil: &str) -> String {
    let good_sum = good.to_string().split(" ").into_iter()
        .zip([1, 2, 3, 3, 4, 10].into_iter())
        .fold(0, |acc, (number, worth)| acc + (number.to_string().parse::<i32>().unwrap() * worth));
    let evil_sum = evil.to_string().split(" ").into_iter()
        .zip([1, 2, 2, 2, 3, 5, 10].into_iter())
        .fold(0, |acc, (number, worth)| acc + (number.to_string().parse::<i32>().unwrap() * worth));
    if good_sum > evil_sum {
        return String::from("Battle Result: Good triumphs over Evil");
    }
    if good_sum < evil_sum {
        return String::from("Battle Result: Evil eradicates all trace of Good");
    }
    String::from("Battle Result: No victor on this battle field")
}

#[test]
fn returns_expected() {
    assert_eq!(good_vs_evil("0 0 0 0 0 10", "0 0 0 0 0 0 0"), "Battle Result: Good triumphs over Evil");
    assert_eq!(good_vs_evil("0 0 0 0 0 0", "0 0 0 0 0 0 10"), "Battle Result: Evil eradicates all trace of Good");
    assert_eq!(good_vs_evil("0 0 0 0 0 10", "0 0 0 0 0 0 10"), "Battle Result: No victor on this battle field");
    assert_eq!(good_vs_evil("0 1 0 5 0 10", "0 2 0 0 0 4 1"), "Battle Result: Good triumphs over Evil");
    assert_eq!(good_vs_evil("0 4 0 0 20 10", "0 0 3 3 3 0 10"), "Battle Result: Good triumphs over Evil");
    assert_eq!(good_vs_evil("0 0 2 4 4 10", "4 4 0 0 0 0 4"), "Battle Result: Good triumphs over Evil");
    assert_eq!(good_vs_evil("1 1 1 1 1 1", "1 1 1 1 1 1 1"), "Battle Result: Evil eradicates all trace of Good");
    assert_eq!(good_vs_evil("4 0 9 0 70 0", "0 20 10 30 0 40 10"), "Battle Result: Evil eradicates all trace of Good");
    assert_eq!(good_vs_evil("123123123 0 0 0 0 10", "11215 0 0 125 0 215 10"), "Battle Result: Good triumphs over Evil");
    assert_eq!(good_vs_evil("12 0 0 0 124 10", "214 0 1240 0 40 0 1240"), "Battle Result: Evil eradicates all trace of Good");
}