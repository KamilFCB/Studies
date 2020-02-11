fn last_digit(str1: &str, str2: &str) -> i32 {
    if str2.to_string().chars().last().unwrap().to_digit(10).unwrap() == 0 && str2.len() == 1 {
        return 1
    }

    let a: i32 = str1.to_string().chars().last().unwrap().to_digit(10).unwrap() as i32;
    if a == 1 || a == 5 || a == 6 || a == 0{
        return a;
    }

    let modulo: i32;
    let mut b:i32;
    if a == 2 || a == 3 || a == 7 || a == 8 {
        modulo = 4;
        if str2.len() > 1 {
            b = (str2.to_string().chars().nth(str2.len() - 2).unwrap().to_digit(10).unwrap() as i32) * 10;
            b += str2.to_string().chars().nth(str2.len() - 1).unwrap().to_digit(10).unwrap() as i32
        } else {
            b = str2.to_string().chars().last().unwrap().to_digit(10).unwrap() as i32;
        }
    } else {
        modulo = 2;
        b = str2.to_string().chars().last().unwrap().to_digit(10).unwrap() as i32;
    }

    let mut rest: u32 = (b % modulo) as u32;
    if rest == 0 {
        rest += modulo as u32;
    }

    a.pow(rest).to_string().chars().last().unwrap().to_digit(10).unwrap() as i32
}

fn main() {
    println!("{}", last_digit("4", "2"));
}

#[test]
fn returns_expected() {
    assert_eq!(last_digit("4", "1"), 4);
    assert_eq!(last_digit("0", "0"), 1);
    assert_eq!(last_digit("4", "2"), 6);
    assert_eq!(last_digit("9", "7"), 9);
    assert_eq!(last_digit("74", "540"), 6);
    assert_eq!(last_digit("1899", "215127"), 9);
    assert_eq!(last_digit("10","10000000000"), 0);
    assert_eq!(last_digit("1606938044258990275541962092341162602522202993782792835301376","2037035976334486086268445688409378161051468393665936250636140449354381299763336706183397376"), 6);
    assert_eq!(last_digit("3715290469715693021198967285016729344580685479654510946723", "68819615221552997273737174557165657483427362207517952651"), 7);
    assert_eq!(last_digit("779983791222217903700245380729112069187418436312434725319310870719680564425647986595221588", "058932369659730084929129899047"), 2);
    assert_eq!(last_digit("927301752969546654854159942012336500997673478702860067","03796703100045280372253467689693207791468149502172059447397253740073241914134"), 9);
}