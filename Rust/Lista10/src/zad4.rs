use regex::Regex;

fn change(s: &str, prog: &str, version: &str) -> String {
    let version_regexp = Regex::new(r"Version: [0-9]+[.][0-9]+\n").unwrap();
    let version2_regexp = Regex::new(r"Version: 2.0\n").unwrap();
    let phone_regexp = Regex::new(r"Phone: \+1-[0-9]{3}-[0-9]{3}-[0-9]{4}").unwrap();

    if phone_regexp.find(s).is_none() || version_regexp.find(s).is_none() {
        return String::from("ERROR: VERSION or PHONE");
    }
    if version2_regexp.find(s).is_some() {
        return format!("Program: {} Author: g964 Phone: +1-503-555-0090 Date: 2019-01-01 Version: 2.0", prog);
    }
    format!("Program: {} Author: g964 Phone: +1-503-555-0090 Date: 2019-01-01 Version: {}", prog, version)
}

#[cfg(test)]
mod tests {
    use super::*;

    fn dotest(s: &str, prog: &str, version: &str, exp: &str) -> () {
        println!("s:{:?}", s);
        println!("prog:{:?}", prog);
        println!("version:{:?}", version);
        let ans = change(s, prog, version);
        println!("actual: {:?}", ans);
        println!("expect: {:?}", exp);
        println!("{}", ans == exp);
        assert_eq!(ans, exp);
        println!("{}", "-");
    }

    #[test]
    fn basic_tests() {
        let s1="Program title: Primes\nAuthor: Kern\nCorporation: Gold\nPhone: +1-503-555-0091\nDate: Tues April 9, 2005\nVersion: 6.7\nLevel: Alpha";
        dotest(s1, "Ladder", "1.1", "Program: Ladder Author: g964 Phone: +1-503-555-0090 Date: 2019-01-01 Version: 1.1");
        let s2="Program title: Balance\nAuthor: Dorries\nCorporation: Funny\nPhone: +1-503-555-0095\nDate: Tues July 19, 2014\nVersion: 6.7\nLevel: Release";
        dotest(s2, "Circular", "1.5", "Program: Circular Author: g964 Phone: +1-503-555-0090 Date: 2019-01-01 Version: 1.5");
        let s3="Program title: Primes\nAuthor: Kern\nCorporation: Gold\nPhone: +1-503-555-0090\nDate: Tues April 9, 2005\nVersion: 67\nLevel: Alpha";
        dotest(s3, "Ladder", "1.1", "ERROR: VERSION or PHONE");
        let s4="Program title: Primes\nAuthor: Kern\nCorporation: Gold\nPhone: +48-503-555-0090\nDate: Tues April 9, 2005\nVersion: 67\nLevel: Alpha";
        dotest(s4, "Ladder", "1.1", "ERROR: VERSION or PHONE");
        let s5="Program title: Primes\nAuthor: Kern\nCorporation: Gold\nPhone: +1-503-555-0090\nDate: Tues April 9, 2005\nVersion: 6.7\nLevel: Alpha";
        dotest(s5, "Alibaba", "1.112", "Program: Alibaba Author: g964 Phone: +1-503-555-0090 Date: 2019-01-01 Version: 1.112");
        let s6="Program title: Primes\nAuthor: Kamil\nCorporation: Silver\nPhone: +1-503-555-1234\nDate: Tues April 9, 1410\nVersion: 6.7\nLevel: Alpha";
        dotest(s6, "SilverG964", "4.4", "Program: SilverG964 Author: g964 Phone: +1-503-555-0090 Date: 2019-01-01 Version: 4.4");
        let s7="Program title: DWEFADW\nAuthor: Kamil\nCorporation: Silver\nPhone: +1-503-555-1234\nDate: Tues April 9, 1410\nVersion: 6.7\nLevel: Alpha";
        dotest(s7, "Bronze", "4.24", "Program: Bronze Author: g964 Phone: +1-503-555-0090 Date: 2019-01-01 Version: 4.24");
        let s8="Program title: ABCD\nAuthor: Kamil\nCorporation: Silver\nPhone: +1-503-555-1234\nDate: Tues April 9, 1410\nVersion: 6.7\nLevel: Alpha";
        dotest(s8, "asdaw", "4.4", "Program: asdaw Author: g964 Phone: +1-503-555-0090 Date: 2019-01-01 Version: 4.4");
        let s9="Program title: jadow\nAuthor: Kamil\nCorporation: Silver\nPhone: +1-503-555-12340\nDate: Tues April 9, 1410\nVersion: 6.7\nLevel: Alpha";
        dotest(s9, "Ladder", "1.1", "Program: Ladder Author: g964 Phone: +1-503-555-0090 Date: 2019-01-01 Version: 1.1");
        let s10="Program title: qwirpq\nAuthor: Kamil\nCorporation: Silver\nPhone: +1-503-55445-12ads34\nDate: Tues April 9, 1410\nVersion: 6.7\nLevel: Alpha";
        dotest(s10, "asdaw", "4.1", "ERROR: VERSION or PHONE");
    }
}
