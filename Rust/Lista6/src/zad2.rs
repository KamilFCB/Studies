fn dig_pow(n: i64, p: i32) -> i64 {
    let sum: i64 = ((p as usize)..=(p as usize) + n.to_string().len()).into_iter()
        .zip(n.to_string().chars().into_iter())
        .fold(0 as i64, |acc, (power, digit)| acc + (digit.to_digit(10).unwrap() as u64).pow(power as u32) as i64);
    if sum % n == 0 {
        return sum / n;
    }
    -1
}

#[cfg(test)]
mod tests {
    use super::*;

    fn dotest(n: i64, p: i32, exp: i64) -> () {
        println!(" n: {:?};", n);
        println!("p: {:?};", p);
        let ans = dig_pow(n, p);
        println!(" actual:\n{:?};", ans);
        println!("expect:\n{:?};", exp);
        println!(" {};", ans == exp);
        assert_eq!(ans, exp);
        println!("{};", "-");
    }

    #[test]
    fn basic_tests() {
        dotest(89, 1, 1);
        dotest(92, 1, -1);
        dotest(46288, 3, 51);
        dotest(5125, 4, -1);
        dotest(1231, 2, -1);
        dotest(351788, 1, -1);
        dotest(125, 6, -1);
        dotest(9421, 3, -1);
        dotest(216, 6, -1);
        dotest(1091, 3, -1);

    }
}
