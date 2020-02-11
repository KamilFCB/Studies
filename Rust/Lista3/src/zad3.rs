use std::collections::HashMap;

struct Cipher {
    encode_map: HashMap<char, char>,
    decode_map: HashMap<char, char>,
}

impl Cipher {
    fn new(map1: &str, map2: &str) -> Cipher {
        let mut encode_map = HashMap::new();
        let mut decode_map = HashMap::new();
        for (ch1, ch2) in map1.chars().into_iter().zip((map2.chars())) {
            encode_map.insert(ch1, ch2);
        }

        for (ch1, ch2) in map2.chars().into_iter().zip((map1.chars())) {
            decode_map.insert(ch1, ch2);
        }

        Cipher{encode_map, decode_map}
    }

    fn encode(&self, string: &str) -> String {
       string.chars().into_iter().map(|ch| {
           if self.encode_map.get(&ch) == None {
               ch
           } else {
               *(self.encode_map.get(&ch).unwrap())
           }
       }).collect()

   }

   fn decode(&self, string: &str) -> String {
       string.chars().into_iter().map(|ch| {
           if self.decode_map.get(&ch) == None {
               ch
           } else {
               *(self.decode_map.get(&ch).unwrap())
           }
       }).collect()
   }
}

fn main() {
    let map1 = "abcdefghijklmnopqrstuvwxyz";
    let map2 = "etaoinshrdlucmfwypvbgkjqxz";

    let cipher = Cipher::new(map1, map2);
    println!("{}", cipher.decode("eta"));
    println!("{}", cipher.encode("abc"));
}

#[test]
fn examples() {
    let map1 = "abcdefghijklmnopqrstuvwxyz";
    let map2 = "etaoinshrdlucmfwypvbgkjqxz";

    let cipher = Cipher::new(map1, map2);

    assert_eq!(cipher.encode("abc"), "eta");
    assert_eq!(cipher.encode("xyz"), "qxz");
    assert_eq!(cipher.encode("jdjqwodqlaksjd"), "dodyjfoyuelvdo");
    assert_eq!(cipher.encode("kjdashdkjad"), "ldoevholdeo");
    assert_eq!(cipher.encode("alamakota"), "euecelfbe");
    assert_eq!(cipher.decode("eta"), "abc");
    assert_eq!(cipher.decode("eirfg"), "aeiou");
    assert_eq!(cipher.decode("erlang"), "aikcfu");
    assert_eq!(cipher.decode("uiqwmnasmnmhdwiuad"), "lexpnfcgnfnhjpelcj");
    assert_eq!(cipher.decode("mkahwiuqwrsjada"), "nvchpelxpigwcjc");
}