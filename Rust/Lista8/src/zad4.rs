impl MorseDecoder {

    fn decode_morse(&self, encoded: &str) -> String {
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

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_hey_jude() {
        let decoder = MorseDecoder::new();
        assert_eq!(decoder.decode_morse(".... . -.--   .--- ..- -.. ."), "HEY JUDE");
        assert_eq!(decoder.decode_morse(".. -. ..-. --- .-. -- .- - -.-- -.- .-"), "INFORMATYKA");
        assert_eq!(decoder.decode_morse(".--. .-. --- --. .-. .- -- --- .-- .- -. .. ."), "PROGRAMOWANIE");
        assert_eq!(decoder.decode_morse("..- -. .. .-- . .-. ... -.-- - . -   .-- .-. --- -.-. .-.. .- .-- ... -.- .."), "UNIWERSYTET WROCLAWSKI");
        assert_eq!(decoder.decode_morse(".-- .-. --- -.-. .-.. .- .--"), "WROCLAW");
        assert_eq!(decoder.decode_morse(".-. ..- ... -"), "RUST");
        assert_eq!(decoder.decode_morse(".- .-.. .-   -- .-   -.- --- - .-"), "ALA MA KOTA");
        assert_eq!(decoder.decode_morse("-.- --- -   -- .-   .- .-.. ."), "KOT MA ALE");
        assert_eq!(decoder.decode_morse(".--. --- .-.. ... -.- .-"), "POLSKA");
        assert_eq!(decoder.decode_morse(". ..- .-. --- .--. .-"), "EUROPA");
    }
}