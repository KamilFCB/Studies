fn encode(msg: String, n: i32) -> Vec<i32> {
    msg.chars().zip(n.to_string().chars().into_iter().cycle()).map(|(ch, k)| (ch as i32) - ('a' as i32) + 1  + k.to_digit(10).unwrap() as i32).collect()
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn fixed_tests() {
        assert_eq!(encode("scout".to_string(), 1939), vec![20, 12, 18, 30, 21]);
        assert_eq!(encode("masterpiece".to_string(), 1939), vec![14, 10, 22, 29, 6, 27, 19, 18, 6, 12, 8]);
        assert_eq!(encode("ala".to_string(), 1939), vec![2, 21, 4]);
        assert_eq!(encode("ma".to_string(), 1939), vec![14, 10]);
        assert_eq!(encode("informatyka".to_string(), 1939), vec![10, 23, 9, 24, 19, 22, 4, 29, 26, 20, 4]);
        assert_eq!(encode("programowanie".to_string(), 1939), vec![17, 27, 18, 16, 19, 10, 16, 24, 24, 10, 17, 18, 6]);
        assert_eq!(encode("wroclaw".to_string(), 1939), vec![24, 27, 18, 12, 13, 10, 26]);
        assert_eq!(encode("uniwersytet".to_string(), 1939), vec![22, 23, 12, 32, 6, 27, 22, 34, 21, 14, 23]);
        assert_eq!(encode("grunwald".to_string(), 125), vec![8, 20, 26, 15, 25, 6, 13, 6]);
        assert_eq!(encode("tramwaj".to_string(), 975), vec![29, 25, 6, 22, 30, 6, 19]);
    }
}