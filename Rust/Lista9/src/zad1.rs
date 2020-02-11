use itertools::join;

fn part_list(arr: Vec<&str>) -> String {
    let mut result: String = "".to_string();
    for i in 1..arr.len() {
        result.push('(');
        result.push_str(&join(&arr[0..i], " ").to_string());
        result.push_str(", ");
        result.push_str(&join(&arr[i..], " ").to_string());
        result.push(')');
    }
    result
}

#[cfg(test)]
mod tests {
    use super::*;

    fn dotest(arr: Vec<&str>, exp: &str) -> () {
        println!("arr: {:?}", arr);
        let ans = part_list(arr);
        println!("actual:\n{}", ans);
        println!("expect:\n{}", exp);
        println!("{}", ans == exp);
        assert_eq!(ans, exp);
        println!("{}", "-");
    }

    #[test]
    fn basis_tests() {
        dotest(vec!["I", "wish", "I", "hadn't", "come"],
               "(I, wish I hadn't come)(I wish, I hadn't come)(I wish I, hadn't come)(I wish I hadn't, come)");
        dotest(vec!["cdIw", "tzIy", "xDu", "rThG"],
               "(cdIw, tzIy xDu rThG)(cdIw tzIy, xDu rThG)(cdIw tzIy xDu, rThG)");
        dotest(vec!["abc", "def", "ghi", "jkl"],
               "(abc, def ghi jkl)(abc def, ghi jkl)(abc def ghi, jkl)");
        dotest(vec!["abc"],
               "");
        dotest(vec![],
               "");
        dotest(vec!["abc", "def"],
               "(abc, def)");
        dotest(vec!["ala", "ma", "kota"],
               "(ala, ma kota)(ala ma, kota)");
        dotest(vec!["kot", "ma", "ale"],
               "(kot, ma ale)(kot ma, ale)");
        dotest(vec!["ala", "ma", "kota", "kot", "ma", "ale"],
               "(ala, ma kota kot ma ale)(ala ma, kota kot ma ale)(ala ma kota, kot ma ale)(ala ma kota kot, ma ale)(ala ma kota kot ma, ale)");
        dotest(vec!["instytut", "informatyki", "uniwersytetu", "wroclawskiego"],
               "(instytut, informatyki uniwersytetu wroclawskiego)(instytut informatyki, uniwersytetu wroclawskiego)(instytut informatyki uniwersytetu, wroclawskiego)");
    }
}
