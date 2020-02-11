fn next_bigger_number(n: i64) -> i64 {
    let s: String = n.to_string();
    let mut prev_digit = s.chars().nth(0).unwrap();
    let length = s.len();
    let mut max_i = 0;
    for i in 1..length {
        let current = s.chars().nth(i).unwrap();
        if prev_digit < current {
            max_i = i;
        }
        prev_digit = current;
    }
    if max_i == 0 {
        return -1;
    }
    max_i -= 1;
    let mut max_j = 0;
    for i in max_i..length {
        let current = s.chars().nth(i).unwrap();
        if current > s.chars().nth(max_i).unwrap() {
            max_j = i;
        }
    }
    if max_j == 0 {
        return -1;
    }

    let mut swaped: String = "".to_string();
    for i in 0..length {
        if i == max_i {
            swaped.push(s.chars().nth(max_j).unwrap());
        } else if i == max_j {
            swaped.push(s.chars().nth(max_i).unwrap());
        } else {
            swaped.push(s.chars().nth(i).unwrap());
        }
    }

    max_i += 1;
    let mut result: String = swaped[0..max_i].to_string();
    let suffix: String = swaped[max_i..length].chars().into_iter().rev().collect();
    for ch in suffix.chars() {
        result.push(ch);
    }

    result.parse::<i64>().unwrap()
}

fn main() {
    println!("{}", next_bigger_number(213));
}


#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn basic() {
        assert_eq!(21, next_bigger_number(12));
        assert_eq!(531, next_bigger_number(513));
        assert_eq!(2071, next_bigger_number(2017));
        assert_eq!(441, next_bigger_number(414));
        assert_eq!(-1, next_bigger_number(9876543210));
        assert_eq!(-1, next_bigger_number(1));
        assert_eq!(-1, next_bigger_number(10));
        assert_eq!(1462113, next_bigger_number(1461321));
        assert_eq!(81149, next_bigger_number(49811));
        assert_eq!(987197898479, next_bigger_number(987197897984));
        assert_eq!(2316874988, next_bigger_number(2316874898));

    }
}