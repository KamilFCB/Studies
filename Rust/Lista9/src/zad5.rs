mod solution {

    pub fn range_extraction(a: &[i32]) -> String {
        let mut result = Vec::new();
        result.push((a[0], a[0]));
        let mut counter = 0;
        for i in 1..a.len() {
            let curr = a[i];
            let prev = result.last().unwrap().1;
            if curr == prev + 1 {
                result[counter].1 = curr;
            } else {
                result.push((curr, curr));
                counter += 1;
            }
        }
        let mut string_res: String = "".to_string();
        for (x, y) in result.into_iter() {
            string_res.push_str(&x.to_string());
            if y - x > 1 {
                string_res.push('-');
                string_res.push_str(&y.to_string());
            }
            if y - x == 1 {
                string_res.push(',');
                string_res.push_str(&y.to_string());
            }
            string_res.push(',');
        }
        string_res.pop();
        string_res
    }
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn example() {
        assert_eq!("-6,-3-1,3-5,7-11,14,15,17-20", solution::range_extraction(&[-6,-3,-2,-1,0,1,3,4,5,7,8,9,10,11,14,15,17,18,19,20]));
        assert_eq!("-3--1,2,10,15,16,18-20", solution::range_extraction(&[-3,-2,-1,2,10,15,16,18,19,20]));
        assert_eq!("1", solution::range_extraction(&[1]));
        assert_eq!("1,100", solution::range_extraction(&[1, 100]));
        assert_eq!("1,2,10,20", solution::range_extraction(&[1, 2, 10, 20]));
        assert_eq!("1-10", solution::range_extraction(&[1, 2, 3, 4, 5, 6, 7, 8, 9, 10]));
        assert_eq!("-2-2,10,102,124", solution::range_extraction(&[-2, -1, 0, 1, 2, 10, 102, 124]));
        assert_eq!("1,215,291,2142-2144", solution::range_extraction(&[1, 215, 291, 2142, 2143, 2144]));
        assert_eq!("-100,-99,-97,-96,-50,0,1,215", solution::range_extraction(&[-100, -99, -97, -96, -50, 0, 1, 215]));
        assert_eq!("-125,-120,125,1255,91285", solution::range_extraction(&[-125, -120, 125, 1255, 91285]));
    }
}
