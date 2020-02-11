fn xo(string: &'static str) -> bool {
    let str: String = string.to_string();
    str.chars().into_iter().filter(|ch| *ch == 'x' || *ch == 'X').count() == str.chars().into_iter().filter(|ch| *ch == 'o' || *ch == 'O').count()

}

#[test]
fn returns_expected() {
    assert_eq!(xo("xo"), true);
    assert_eq!(xo("Xo"), true);
    assert_eq!(xo("xxOo"), true);
    assert_eq!(xo("xxxm"), false);
    assert_eq!(xo("Oo"), false);
    assert_eq!(xo("ooom"), false);
    assert_eq!(xo("xoXOoXxo"), true);
    assert_eq!(xo("XxXxXXooOo"), false);
    assert_eq!(xo("xxOooooXXXXXXXXXoXo"), false);
    assert_eq!(xo("xxxdjwoqjasjdoawidjaowidaowoadjawdoam"), false);
}