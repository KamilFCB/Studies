fn longest(a1: &str, a2: &str) -> String {

    let s1: String = a1.to_string();
    let s2: String = a2.to_string();
    let mut res: String = "".to_string();
    let mut c: char = 'a';

    for i in 0..26 {
        c = std::char::from_u32('a' as u32 + i).unwrap_or(c);
        if s1.contains(c) || s2.contains(c) {
            res.push(c)
        }
    }

    res
}

fn main() {
    println!("{}", longest("abc", "cbz"));
}

#[cfg(test)]
mod tests {
    use super::*;

    fn testing(s1: &str, s2: &str, exp: &str) -> () {
        println!("s1:{:?} s2:{:?}", s1, s2);
        println!("{:?} {:?}", longest(s1, s2), exp);
        println!("{}", longest(s1, s2) == exp);
        assert_eq!(&longest(s1, s2), exp)
    }

    #[test]
    fn basic_tests() {
        testing("aretheyhere", "yestheyarehere", "aehrsty");
        testing("loopingisfunbutdangerous", "lessdangerousthancoding", "abcdefghilnoprstu");
        testing("aaaaaaaaaa", "", "a");
        testing("", "bbbb", "b");
        testing("cba", "abc", "abc");
        testing("dgaga", "awgsbqwtgasgqe", "abdegqstw");
        testing("abcdefghabcdefghz", "ijklmnopqrstuv", "abcdefghijklmnopqrstuvz");

    }
}
