use std::cmp;

impl MorseDecoder {
    pub fn decode_bits(&self, encoded: &str) -> String {
        let mut min: u32 = 999999;
        let mut counter: u32 = 0;
        let mut last = '1';
        let new_encoded: String = encoded.to_string().trim_end_matches('0').trim_start_matches('0').to_string();
        for current in new_encoded.chars() {
            if last == current {
                counter += 1;
            } else {
                min = cmp::min(min, counter);
                counter = 1;
            }
            last = current;
        }
        min = cmp::min(min, counter);
        let result: String = new_encoded.replace(&"1".repeat((3 * min) as usize), "-")
            .replace(&"1".repeat(min as usize), ".")
            .replace(&"0".repeat((7 * min) as usize), "   ")
            .replace(&"0".repeat((3 * min) as usize), " ")
            .replace(&"0".repeat(min as usize), "");
        result
    }

    pub fn decode_morse(&self, encoded: &str) -> String {
        let mut result: String = "".to_string();
        for code in encoded.replace("   ", "  ").split(" ") {
            if code.trim().len() == 0 {
                result.push(' ');
            } else {
                result += &self.morse_code[code];
            }
        }
        result.trim().to_string()
    }
}

#[test]
fn examples() {
    let decoder = MorseDecoder::new();
    assert_eq!(decoder.decode_morse(&decoder.decode_bits("1100110011001100000011000000111111001100111111001111110000000000000011001111110011111100111111000000110011001111110000001111110011001100000011")), "HEY JUDE".to_string());
}