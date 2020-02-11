fn solution(n: f64) -> f64 {
    let modulo: f64 = n % 0.5;
    if modulo < 0.25 {
        return n - modulo;
    }
    n + (0.5 - modulo)
}

#[cfg(test)]
mod tests {
    use super::solution;

    #[test]
    fn sample_tests() {
        assert_eq!(solution(4.2), 4.0);
        assert_eq!(solution(4.4), 4.5);
        assert_eq!(solution(4.6), 4.5);
        assert_eq!(solution(4.8), 5.0);
        assert_eq!(solution(4.0), 4.0);
        assert_eq!(solution(4.24), 4.0);
        assert_eq!(solution(4.25), 4.5);
        assert_eq!(solution(4.499999), 4.5);
        assert_eq!(solution(4.50), 4.5);
        assert_eq!(solution(4.5000000001), 4.5);
    }
}