fn summy(strng: &str) -> i32 {
    strng.split(" ").into_iter().map(|s| s.parse::<i32>().unwrap()).sum()
}

fn main() {
    println!("{}", summy("10 10"));
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn sample_tests() {
        assert_eq!(summy("1 2 3"), 6);
        assert_eq!(summy("1 2 3 4"), 10);
        assert_eq!(summy("1 2 3 4 5"), 15);
        assert_eq!(summy("10 10"), 20);
        assert_eq!(summy("100 0"), 100);
        assert_eq!(summy("0 0"), 0);
        assert_eq!(summy("5 10 20 30 2"), 67);
        assert_eq!(summy("2 0 10 0 1"), 13);
        assert_eq!(summy("2124 12310 75574 4574 21372"), 115954);
        assert_eq!(summy("98712958 21 1 0 1928172515"), 2026885495);
        assert_eq!(summy("22 05 120 20 1122"), 1289);
    }
}