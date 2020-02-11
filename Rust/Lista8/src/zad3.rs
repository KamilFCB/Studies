fn factorial(num: u64) -> u64 {
    match num {
        0 => 1,
        1 => 1,
        _ => factorial(num - 1) * num,
    }
}

fn dec2_fact_string(nb: u64) -> String {
    let mut res: String = "".to_string();
    let mut sum: u64 = nb;
    let mut first_digit_flag = 0;
    for i in (0..21).rev() {
        let fact = factorial(i as u64);
        let mut counter: u8 = 0;
        while sum >= fact {
            sum -= fact;
            counter += 1;
        }
        if counter > 0 || first_digit_flag == 1 {
            let mut digit = counter.to_string();
            if counter >= 10 {
                digit = (((counter - 10) + ('A' as u8)) as char).to_string();
            }
            res.push_str(&digit);
            first_digit_flag = 1;
        }
    }
    res
}

fn fact_string_2dec(s: String) -> u64 {
    s.chars().into_iter()
        .zip((0..s.len()).into_iter().rev())
        .fold(0, |acc, (cyfra, silnia)| acc + (cyfra.to_digit(36).unwrap() as u64) * factorial(silnia as u64)) as u64
}

fn testing1(nb: u64, exp: &str) -> () {
    assert_eq!(&dec2_fact_string(nb), exp)
}

fn testing2(s: &str, exp: u64) -> () {
    assert_eq!(fact_string_2dec(s.to_string()), exp)
}

#[test]
fn basics_dec2_fact_string() {

    testing1(2982, "4041000");
    testing1(463, "341010");
    testing1(51251, "121101210");
    testing1(123, "100110");
    testing1(95821, "230022010");
}
#[test]
fn basics_fact_string_2dec() {

    testing2("4041000", 2982);
    testing2("341010", 463);
    testing2("A940000000000", 5163782400);
    testing2("55122121000", 20010414);
    testing2("78421121100", 28476896);

}