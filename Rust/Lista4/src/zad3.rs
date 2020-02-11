use regex::Regex;

pub fn highlight(code: &str) -> String {
    let regexp_f = Regex::new(r"(?P<f>[F]+)").unwrap();
    let regexp_r = Regex::new(r"(?P<r>[R]+)").unwrap();
    let regexp_d = Regex::new(r"(?P<d>[0-9]+)").unwrap();
    let regexp_l = Regex::new(r"(?P<l>[L]+)").unwrap();
    let mut result: String = regexp_f.replace_all(&code, "<span style=\"color: pink\">$f</span>").to_string();
    result = regexp_r.replace_all(&result, "<span style=\"color: green\">$r</span>").to_string();
    result = regexp_d.replace_all(&result, "<span style=\"color: orange\">$d</span>").to_string();
    regexp_l.replace_all(&result, "<span style=\"color: red\">$l</span>").to_string()
}

#[cfg(test)]
mod tests {
    use super::*;

    #[cfg(test)]
    macro_rules! assert_highlight {
        ($code:expr , $expected:expr $(,)*) => {{
            let actual = highlight($code);
            let expected = $expected;
            println!("Code without syntax highlighting: {}", $code);
            println!("Your code with syntax highlighting: {}", actual);
            println!("Expected syntax highlighting: {}", expected);
            assert_eq!(actual, expected);
        }};
    }

    #[test]
    fn examples_in_description() {
        assert_highlight!(
            "F3RF5LF7",
            r#"<span style="color: pink">F</span><span style="color: orange">3</span><span style="color: green">R</span><span style="color: pink">F</span><span style="color: orange">5</span><span style="color: red">L</span><span style="color: pink">F</span><span style="color: orange">7</span>"#,
        );
        assert_highlight!(
            "FFFR345F2LL",
            r#"<span style="color: pink">FFF</span><span style="color: green">R</span><span style="color: orange">345</span><span style="color: pink">F</span><span style="color: orange">2</span><span style="color: red">LL</span>"#,
        );
        assert_highlight!(
            "FFF(R)345F(2)LL",
            r#"<span style="color: pink">FFF</span>(<span style="color: green">R</span>)<span style="color: orange">345</span><span style="color: pink">F</span>(<span style="color: orange">2</span>)<span style="color: red">LL</span>"#,
        );
        assert_highlight!(
            "FR0123456978LLR",
            r#"<span style="color: pink">F</span><span style="color: green">R</span><span style="color: orange">0123456978</span><span style="color: red">LL</span><span style="color: green">R</span>"#,
        );
        assert_highlight!(
            "FRLF25L1RLFR1L131RFLRF0219",
            r#"<span style="color: pink">F</span><span style="color: green">R</span><span style="color: red">L</span><span style="color: pink">F</span><span style="color: orange">25</span><span style="color: red">L</span><span style="color: orange">1</span><span style="color: green">R</span><span style="color: red">L</span><span style="color: pink">F</span><span style="color: green">R</span><span style="color: orange">1</span><span style="color: red">L</span><span style="color: orange">131</span><span style="color: green">R</span><span style="color: pink">F</span><span style="color: red">L</span><span style="color: green">R</span><span style="color: pink">F</span><span style="color: orange">0219</span>"#,
        );
        assert_highlight!(
            "FLRLFRLFLRFLRLFLRFLRLFFFFFLLLLLRRRRRRRRRRRRRRRRRRRRRRRRRR",
            r#"<span style="color: pink">F</span><span style="color: red">L</span><span style="color: green">R</span><span style="color: red">L</span><span style="color: pink">F</span><span style="color: green">R</span><span style="color: red">L</span><span style="color: pink">F</span><span style="color: red">L</span><span style="color: green">R</span><span style="color: pink">F</span><span style="color: red">L</span><span style="color: green">R</span><span style="color: red">L</span><span style="color: pink">F</span><span style="color: red">L</span><span style="color: green">R</span><span style="color: pink">F</span><span style="color: red">L</span><span style="color: green">R</span><span style="color: red">L</span><span style="color: pink">FFFFF</span><span style="color: red">LLLLL</span><span style="color: green">RRRRRRRRRRRRRRRRRRRRRRRRRR</span>"#,
        );
        assert_highlight!(
            "FFFFFFFFL15",
            r#"<span style="color: pink">FFFFFFFF</span><span style="color: red">L</span><span style="color: orange">15</span>"#,
        );
        assert_highlight!(
            "()()()()()()()()()()()()()()(F)",
            r#"()()()()()()()()()()()()()()(<span style="color: pink">F</span>)"#,
        );
        assert_highlight!(
            "(F)(R)(L)(0)",
            r#"(<span style="color: pink">F</span>)(<span style="color: green">R</span>)(<span style="color: red">L</span>)(<span style="color: orange">0</span>)"#,
        );
        assert_highlight!(
            "FLRLFLRLFR",
            r#"<span style="color: pink">F</span><span style="color: red">L</span><span style="color: green">R</span><span style="color: red">L</span><span style="color: pink">F</span><span style="color: red">L</span><span style="color: green">R</span><span style="color: red">L</span><span style="color: pink">F</span><span style="color: green">R</span>"#,
        );
    }
}