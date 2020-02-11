fn dbl_linear(n: u32) -> u32{
    let mut result = vec![1];
    let mut current_y;
    let mut current_z;
    let mut y_counter: usize = 0;
    let mut z_counter: usize = 0;
    for i in 1..(2*n) {
        current_y = result[y_counter] * 2 + 1;
        current_z = result[z_counter] * 3 + 1;
        if current_y < current_z {
            result.push(current_y);
            y_counter += 1;
        } else if current_z < current_y {
            result.push(current_z);
            z_counter += 1;
        } else {
            result.push(current_z);
            z_counter += 1;
            y_counter += 1;
        }
    }
    result[n as usize] as u32
}

#[cfg(test)]
mod tests {
    use super::dbl_linear;
    fn testing(n: u32, exp: u32) -> () {
        assert_eq!(dbl_linear(n), exp)
    }
    #[test]
    fn basics_dbl_linear() {
        testing(10, 22);
        testing(20, 57);
        testing(30, 91);
        testing(50, 175);
        testing(100, 447);
        testing(200, 1051);
        testing(500, 3355);
        testing(1000, 8488);
        testing(10000, 157654);
        testing(100000, 2911582);
    }
}