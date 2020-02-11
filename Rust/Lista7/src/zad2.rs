use std::collections::BTreeMap;

fn letter_frequency(input: &str) -> BTreeMap<char, i32> {
    let mut result: BTreeMap<char, i32> = BTreeMap::new();
    for ch in input.to_lowercase().chars() {
        if !ch.is_alphabetic() {
            continue;
        }
        if let Some(x) = result.get_mut(&ch) {
            *x = *x + 1;
        } else {
            result.insert(ch, 1);
        }
    }
    result
}

#[cfg(test)]
mod tests {
    use std::collections::BTreeMap;
    use super::letter_frequency;

    #[test]
    fn simpleword() {
        let answer: BTreeMap<char, i32> =
            [('a', 2),
                ('c', 1),
                ('l', 1),
                ('t', 1),
                ('u', 1)]
                .iter().cloned().collect();

        assert_eq!(letter_frequency("actual"), answer);
    }

    #[test]
    fn sequence() {
        let answer: BTreeMap<char, i32> =
            [('a', 3),
                ('b', 2),
                ('f', 1),
                ('p', 1),
                ('s', 1),
                ('t', 2),
                ('u', 1),
                ('x', 5)]
                .iter().cloned().collect();

        assert_eq!(letter_frequency("AaabBF UttsP xxxxx"), answer);
    }

    #[test]
    fn test1() {
        let answer: BTreeMap<char, i32> =
            [('a', 6),
                ('d', 4),
                ('j', 4),
                ('k', 4),
                ('l', 3),
                ('n', 1),
                ('s', 1),
                ('w', 5)]
                .iter().cloned().collect();

        assert_eq!(letter_frequency("djkalw Alkjdwa ASDKJALWKDJWANW"), answer);
    }

    #[test]
    fn test2() {
        let answer: BTreeMap<char, i32> =
            [('a', 1),
                ('e', 1),
                ('i', 1),
                ('k', 1),
                ('m', 1),
                ('o', 1),
                ('q', 1),
                ('w', 1)]
                .iter().cloned().collect();

        assert_eq!(letter_frequency("kwoameiq"), answer);
    }

    #[test]
    fn test3() {
        let answer: BTreeMap<char, i32> =
            [('a', 2),
                ('d', 1),
                ('i', 2),
                ('j', 1),
                ('m', 5),
                ('w', 2)]
                .iter().cloned().collect();

        assert_eq!(letter_frequency("MDMMAWIMMAIJW"), answer);
    }

    #[test]
    fn test4() {
        let answer: BTreeMap<char, i32> =
            [('a', 2),
                ('d', 1),
                ('i', 2),
                ('j', 1),
                ('m', 5),
                ('w', 2)]
                .iter().cloned().collect();

        assert_eq!(letter_frequency("mdmmawimmaijw"), answer);
    }

    #[test]
    fn test5() {
        let answer: BTreeMap<char, i32> =
            [('a', 4),
                ('k', 1),
                ('l', 1),
                ('m', 1),
                ('o', 1),
                ('t', 1)]
                .iter().cloned().collect();

        assert_eq!(letter_frequency("ala ma kota"), answer);
    }

    #[test]
    fn test6() {
        let answer: BTreeMap<char, i32> =
            [('a', 2),
                ('e', 1),
                ('k', 1),
                ('l', 1),
                ('m', 1),
                ('o', 1),
                ('t', 1)]
                .iter().cloned().collect();

        assert_eq!(letter_frequency("kot ma ale"), answer);
    }

    #[test]
    fn test7() {
        let answer: BTreeMap<char, i32> =
            [('r', 1),
                ('u', 1),
                ('s', 1),
                ('t', 1)]
                .iter().cloned().collect();

        assert_eq!(letter_frequency("rust"), answer);
    }

    #[test]
    fn test8() {
        let answer: BTreeMap<char, i32> =
            [('a', 2),
                ('f', 1),
                ('i', 1),
                ('k', 1),
                ('m', 1),
                ('n', 1),
                ('o', 1),
                ('r', 1),
                ('t', 1),
                ('y', 1)]
                .iter().cloned().collect();

        assert_eq!(letter_frequency("informatyka"), answer);
    }

}