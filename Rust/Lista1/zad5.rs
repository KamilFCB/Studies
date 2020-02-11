fn printer_error(s: &str) -> String {
    let res: String = s.chars().filter(|&ch| ch < 'a' || ch > 'm').collect();
    format!("{}/{}", res.len(), s.len())
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn should_pass_all_the_tests_provided() {
        assert_eq!(&printer_error("aaaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmxyz"), "3/56");
        assert_eq!(&printer_error("kkkwwwaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmxyz"), "6/60");
        assert_eq!(&printer_error("kkkwwwaaaaaaaaaaaaaabbbbbbbbbbbbbbbbbbmmmmmmmmmmmmmmmmmmmxyzuuuuu"), "11/65");
        assert_eq!(&printer_error("qwrtyuopsxzv"), "12/12");
        assert_eq!(&printer_error("qawaratayauaoapasaxazav"), "12/23");
        assert_eq!(&printer_error("abcabcabcabac"), "0/13");
    }
}