use std::collections::BTreeMap;

fn stock_list(list_art: Vec<&str>, list_cat: Vec<&str>) -> String {
    if list_art.len() == 0 {
        return "".to_string();
    }
    let mut result_map: BTreeMap<String, i32> = BTreeMap::new();
    for art in list_art {
        let pair: Vec<&str> = art.split(' ').collect();
        let ch = pair[0].chars().nth(0).unwrap().to_string();
        println!("{}", ch);
        if let Some(x) = result_map.get_mut(&ch) {
            *x = *x + pair[1].to_string().parse::<i32>().unwrap();
        } else {
            result_map.insert(ch, pair[1].to_string().parse::<i32>().unwrap());
        }
    }
    let mut result = Vec::new();
    for cat in list_cat {
        if let Some(x) = result_map.get(&cat.to_string()) {
            result.push(format!("({} : {:?})", cat, *x));
        } else {
            result.push(format!("({} : 0)", cat));
        }
    }
    itertools::join(&result, " - ")
}

#[cfg(test)]
mod tests {
    use super::*;

    fn dotest(list_art: Vec<&str>, list_cat: Vec<&str>, exp: &str) -> () {
        println!("list_art: {:?};", list_art);
        println!("list_cat: {:?};", list_cat);
        let ans = stock_list(list_art, list_cat);
        println!("actual:\n{:?};", ans);
        println!("expect:\n{:?};", exp);
        println!("{};", ans == exp);
        assert_eq!(ans, exp);
        println!("{};", "-");
    }

    #[test]
    fn basic_tests() {
        let mut b = vec!["BBAR 150", "CDXE 515", "BKWR 250", "BTSQ 890", "DRTY 600"];
        let mut c = vec!["A", "B", "C", "D"];
        dotest(b, c, "(A : 0) - (B : 1290) - (C : 515) - (D : 600)");
        b = vec!["BBAR 150", "CDXE 515", "BKWR 250", "BTSQ 890", "DRTY 600"];
        c = vec!["A", "B"];
        dotest(b, c, "(A : 0) - (B : 1290)");
        b = vec!["BBAR 150", "CDXE 515", "BKWR 250", "BTSQ 890", "DRTY 600"];
        c = vec!["D", "B"];
        dotest(b, c, "(D : 600) - (B : 1290)");
        b = vec!["BBAR 150", "CDXE 515", "BKWR 250", "BTSQ 890", "DRTY 600"];
        c = vec!["C", "A"];
        dotest(b, c, "(C : 515) - (A : 0)");
        b = vec!["BBAR 150", "CDXE 515", "BKWR 250", "BTSQ 890", "DRTY 600"];
        c = vec!["A", "B", "D"];
        dotest(b, c, "(A : 0) - (B : 1290) - (D : 600)");
        b = vec!["ABAR 200", "CDXE 500", "BKWR 250", "BTSQ 890", "DRTY 600"];
        c = vec!["A", "B"];
        dotest(b, c, "(A : 200) - (B : 1140)");
        b = vec!["ABAR 200", "CDXE 500", "BKWR 250", "BTSQ 890", "DRTY 600"];
        c = vec!["A", "C"];
        dotest(b, c, "(A : 200) - (C : 500)");
        b = vec!["ABAR 200", "CDXE 500", "BKWR 250", "BTSQ 890", "DRTY 600"];
        c = vec!["D", "C"];
        dotest(b, c, "(D : 600) - (C : 500)");
        b = vec!["ABAR 200", "CDXE 500", "BKWR 250", "BTSQ 890", "DRTY 600"];
        c = vec!["A", "B", "C", "D"];
        dotest(b, c, "(A : 200) - (B : 1140) - (C : 500) - (D : 600)");
        b = vec!["ABAR 200", "CDXE 500", "BKWR 250", "BTSQ 890", "DRTY 600"];
        c = vec!["A", "B", "D"];
        dotest(b, c, "(A : 200) - (B : 1140) - (D : 600)");

    }
}
