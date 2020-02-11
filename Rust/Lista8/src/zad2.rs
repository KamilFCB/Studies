fn alphabet_position(text: &str) -> String {
    let mut result: String = "".to_string();
    for ch in text.chars() {
        if ch.is_alphabetic() {
            match ch {
                ch if ch.is_lowercase() => result.push_str(&((ch as i8) - ('a' as i8) + 1).to_string()),
                ch if ch.is_uppercase() => result.push_str(&((ch as i8) - ('A' as i8) + 1).to_string()),
                _ => {}
            }
            result.push(' ');
        }
    }
    result.trim_end().to_string()
}

#[test]
fn returns_expected() {
    assert_eq!(
        alphabet_position("The sunset sets at twelve o' clock."),
        "20 8 5 19 21 14 19 5 20 19 5 20 19 1 20 20 23 5 12 22 5 15 3 12 15 3 11".to_string()
    );
    assert_eq!(
        alphabet_position("The narwhal bacons at midnight."),
        "20 8 5 14 1 18 23 8 1 12 2 1 3 15 14 19 1 20 13 9 4 14 9 7 8 20".to_string()
    );
    assert_eq!(
        alphabet_position("Informatyka"),
        "9 14 6 15 18 13 1 20 25 11 1".to_string()
    );
    assert_eq!(
        alphabet_position("Programowanie"),
        "16 18 15 7 18 1 13 15 23 1 14 9 5".to_string()
    );
    assert_eq!(
        alphabet_position("Uniwersytet Wrocławski"),
        "21 14 9 23 5 18 19 25 20 5 20 23 18 15 3 -30 1 23 19 11 9".to_string()
    );
    assert_eq!(
        alphabet_position("Studia nie z tej Ziemii!!"),
        "19 20 21 4 9 1 14 9 5 26 20 5 10 26 9 5 13 9 9".to_string()
    );
    assert_eq!(
        alphabet_position("Rust > C++"),
        "18 21 19 20 3".to_string()
    );
    assert_eq!(
        alphabet_position("Ala ma kota"),
        "1 12 1 13 1 11 15 20 1".to_string()
    );
    assert_eq!(
        alphabet_position("Kot ma Ale"),
        "11 15 20 13 1 1 12 5".to_string()
    );
    assert_eq!(
        alphabet_position("F!%!@%:ajny 1251251test(*@&$!(*%&!(*@%&(*@%&821125"),
        "6 1 10 14 25 20 5 19 20".to_string()
    );
}