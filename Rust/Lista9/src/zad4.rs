fn camel_case(str: &str) -> String {
    if str.len() == 0 {
        return "".to_string();
    }
    let mut result: String = "".to_string();
    for word in str.trim().to_string().split(" ") {
        result.push_str(&word.chars().nth(0).unwrap().to_uppercase().to_string());
        result.push_str(&word[1..].to_string());
    }
    result
}

#[test]
fn sample_test() {
    assert_eq!(camel_case("test case"), "TestCase");
    assert_eq!(camel_case("camel case method"), "CamelCaseMethod");
    assert_eq!(camel_case("say hello "), "SayHello");
    assert_eq!(camel_case(" camel case word"), "CamelCaseWord");
    assert_eq!(camel_case(""), "");
    assert_eq!(camel_case("Ala ma Kota"), "AlaMaKota");
    assert_eq!(camel_case("  kot ma ale    "), "KotMaAle");
    assert_eq!(camel_case("uniwersytet wroclawski"), "UniwersytetWroclawski");
    assert_eq!(camel_case("instytut informatyki uniwersytetu wroclawskiego"), "InstytutInformatykiUniwersytetuWroclawskiego");
    assert_eq!(camel_case("rust jest fajny"), "RustJestFajny");
}