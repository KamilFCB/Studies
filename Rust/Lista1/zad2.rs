fn string_to_number(s: &str) -> i32 {
    s.parse::<i32>().unwrap()
}

fn main() {
    println!("{}", string_to_number("1234"));
}


#[cfg(test)]
mod tests {
    use super::string_to_number;

    #[test]
    fn returns_expected() {
        assert_eq!(string_to_number("1234"), 1234);
        assert_eq!(string_to_number("605"), 605);
        assert_eq!(string_to_number("1405"), 1405);
        assert_eq!(string_to_number("-7"), -7);
        assert_eq!(string_to_number("0"), 0);
    }

    #[test]
    fn bad_results() {
        assert_ne!(string_to_number("-40"), 40);
        assert_ne!(string_to_number("40"), 41);
        assert_ne!(string_to_number("8"), 0);
    }
}