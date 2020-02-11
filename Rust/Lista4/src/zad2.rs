fn even_numbers(array: &Vec<i32>, number: usize) -> Vec<i32> {
    let mut even_numbers: Vec<i32>  = array.iter().cloned().filter(|x| x % 2 == 0).collect();
    (&even_numbers[(even_numbers.len()-number)..even_numbers.len()]).to_vec()
}



#[test]
fn sample_tests() {
    assert_eq!(even_numbers(&vec!(1, 2, 3, 4, 5, 6, 7, 8, 9), 3), vec!(4, 6, 8));
    assert_eq!(even_numbers(&vec!(-22, 5, 3, 11, 26, -6, -7, -8, -9, -8, 26), 2), vec!(-8, 26));
    assert_eq!(even_numbers(&vec!(6, -25, 3, 7, 5, 5, 7, -3, 23), 1), vec!(6));
    assert_eq!(even_numbers(&vec!(2, 3, 5, 9, 11), 1), vec!(2));
    assert_eq!(even_numbers(&vec!(2, 4, 6, 8, 10, 12), 1), vec!(12));
    assert_eq!(even_numbers(&vec!(2, 4, 6, 8, 10, 12), 6), vec!(2, 4, 6, 8, 10, 12));
    assert_eq!(even_numbers(&vec!(-2, -4, -6, -8, -10, -12), 6), vec!(-2, -4, -6, -8, -10, -12));
    assert_eq!(even_numbers(&vec!(-2, -4, 6, 8, -10, -12), 6), vec!(-2, -4, 6, 8, -10, -12));
    assert_eq!(even_numbers(&vec!(214, 92841, 2144, 13, 2800, -2, 15), 2), vec!(2800, -2));
    assert_eq!(even_numbers(&vec!(-2, -1, 0, 1, 2), 3), vec!(-2, 0, 2));
}