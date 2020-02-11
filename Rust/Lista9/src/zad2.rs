fn dont_give_me_five(start: isize, end: isize) -> isize {
    (start..=end).into_iter().fold(0, |acc, x| acc + !x.to_string().contains("5") as isize)
}

// TODO: replace with your own tests (TDD), these are just how-to examples.
// See: https://doc.rust-lang.org/book/testing.html

#[cfg(test)]
mod tests {
    use super::dont_give_me_five;

    #[test]
    fn returns_expected() {
        assert_eq!(dont_give_me_five(1, 9), 8);
        assert_eq!(dont_give_me_five(4, 17), 12);
        assert_eq!(dont_give_me_five(12, 59), 34);
        assert_eq!(dont_give_me_five(4512, 125117), 72495);
        assert_eq!(dont_give_me_five(87251, 128959), 27459);
        assert_eq!(dont_give_me_five(125, 1217), 803);
        assert_eq!(dont_give_me_five(1, 125), 103);
        assert_eq!(dont_give_me_five(515, 1251251), 681939);
        assert_eq!(dont_give_me_five(97715, 125891), 18454);
        assert_eq!(dont_give_me_five(78215, 1275987), 647905);
    }
}