fn print(n: i32) -> Option<String> {
    if n < 1 || n % 2 == 0 {
        return None;
    }
    let mut result: String = "".to_string();
    let mut spaces: i32 = (n-1) / 2;
    let mut asterisks: i32 = 1;
    for i in 1..=n {
        let mut line: String = String::from_utf8(vec![b' '; spaces as usize]).unwrap();
        line += &(String::from_utf8(vec![b'*'; asterisks as usize]).unwrap());
        line += "\n";
        result += &line;
        if (n / i) < 2 {
            spaces += 1;
            asterisks -= 2;
        } else {
            spaces -= 1;
            asterisks += 2;
        }
    }
    Some(result)
}

#[test]
fn basic_test() {
    assert_eq!(print(3), Some(" *\n***\n *\n".to_string()) );
    assert_eq!(print(5), Some("  *\n ***\n*****\n ***\n  *\n".to_string()) );
    assert_eq!(print(-3),None);
    assert_eq!(print(2),None);
    assert_eq!(print(0),None);
    assert_eq!(print(1), Some("*\n".to_string()) );
    assert_eq!(print(7), Some("   *\n  ***\n *****\n*******\n *****\n  ***\n   *\n".to_string()) );
    assert_eq!(print(9), Some("    *\n   ***\n  *****\n *******\n*********\n *******\n  *****\n   ***\n    *\n".to_string()));
    assert_eq!(print(6),None);
    assert_eq!(print(15), Some("       *\n      ***\n     *****\n    *******\n   *********\n  ***********\n *************\n***************\n *************\n  ***********\n   *********\n    *******\n     *****\n      ***\n       *\n".to_string()) );
}