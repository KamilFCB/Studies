use itertools::join;

fn order(sentence: &str) -> String {
    if sentence.len() == 0 {
        return "".to_string();
    }
    let mut vec = Vec::new();
    for i in 1..=9 {
        vec.push(i.to_string());
    }
    let mut length = 0;
    for word in sentence.split(" ") {
        length += 1;
        for i in 1..=9 {
            if word.contains(&i.to_string()) {
                vec.remove(i-1);
                vec.insert(i-1, word.to_string());
            }
        }
    }
    join(&vec[0..length], " ")
}

#[cfg(test)]
mod tests {
    use super::*;
    #[test]
    fn returns_expected() {
        assert_eq!(order("is2 Thi1s T4est 3a"), "Thi1s is2 3a T4est");
        assert_eq!(order(""), "");
        assert_eq!(order("Uniwersy1tet"), "Uniwersy1tet");
        assert_eq!(order("Wrocla2wski Uniwersy1tet"), "Uniwersy1tet Wrocla2wski");
        assert_eq!(order("1 2 3 4 5"), "1 2 3 4 5");
        assert_eq!(order("5 4 3 2 1"), "1 2 3 4 5");
        assert_eq!(order("jdkawjw2adawd kwadk1d djlaw3a 4jaidw 5jaidjwao"), "kwadk1d jdkawjw2adawd djlaw3a 4jaidw 5jaidjwao");
        assert_eq!(order("kj8 jd2 djadiw6 jdaw7 5dan a1a dj3j v4aj"), "a1a jd2 dj3j v4aj 5dan djadiw6 jdaw7 kj8");
        assert_eq!(order("l1 k2 3cx"), "l1 k2 3cx");
        assert_eq!(order("ji1 idja4 lkda2ji mnzca3poo"), "ji1 lkda2ji mnzca3poo idja4");
    }
}