fn get_count(string: &str) -> usize {
    string.chars().filter(|&ch| ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u').count()
}

fn main() {

}

#[test]
fn my_tests() {
    assert_eq!(get_count("abracadabra"), 5);
    assert_eq!(get_count("kamil"), 2);
    assert_eq!(get_count("zzzzz"), 0);
    assert_eq!(get_count(""), 0);
    assert_eq!(get_count("abcdefghijklmnopqrstuvwxz"), 5);
    assert_eq!(get_count("aaaeeeuuoiuoea"), 14);
    assert_eq!(get_count("uniwersytet wroclawski"), 7);
    assert_eq!(get_count("informatyka"), 4);
    assert_eq!(get_count("aaaaaaaaaaaaaaaaeeeeeeeeeeeeeeee"), 32);
}