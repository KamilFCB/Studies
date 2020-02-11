fn count_bits(n: i64) -> u32 {
    let bin: String = format!("{:b}", n);
    let str: &str = &bin;
    str.chars().filter(|&ch| ch == '1').count() as u32
}

fn main() {

    println!("{}", count_bits(20));
}

#[test]
fn returns_expected() {
    assert_eq!(count_bits(0), 0);
    assert_eq!(count_bits(4), 1);
    assert_eq!(count_bits(7), 3);
    assert_eq!(count_bits(9), 2);
    assert_eq!(count_bits(9223372036854775807), 63);
    assert_eq!(count_bits(1025), 2);
    assert_eq!(count_bits(1024), 1);
    assert_eq!(count_bits(1023), 10);
    assert_eq!(count_bits(515), 3);
    assert_eq!(count_bits(9575), 8);
    assert_eq!(count_bits(4987612687), 16);
    assert_eq!(count_bits(56542446548944004), 19);
}