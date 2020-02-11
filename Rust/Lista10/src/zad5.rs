fn interpreter(code: &str, iterations: usize,
               width: usize, height: usize) -> String
{
    println!("{} {} {} {}", code, width, height, iterations);
    let mut result = Vec::new();
    let mut stack = Vec::new();
    let mut pointer = (0 as u32, 0 as u32);
    for _ in 0..height {
        let mut row = Vec::new();
        for _ in 0..width {
            row.push(0);
        }
        result.push(row);
    }

    let mut counter = 0;
    let mut char_counter = 0;

    while counter < iterations && char_counter < code.len() {
        let c = code.chars().nth(char_counter);
        match c {
            Some('n') => {pointer.0 = (pointer.0 as u32).overflowing_sub(1).0; counter += 1;},
            Some('s') => {pointer.0 += 1; counter += 1;},
            Some('e') => {pointer.1 += 1; counter += 1;},
            Some('w') => {pointer.1 = (pointer.1 as u32).overflowing_sub(1).0; counter += 1;},
            Some('*') => {result[pointer.0 as usize][pointer.1 as usize] ^= 1; counter += 1;},
            _ => {}
        }


        if c == Some('[') {
            if result[pointer.0 as usize][pointer.1 as usize] == 0 {
                while code.chars().nth(char_counter) != Some(']') && char_counter < code.len() {
                    char_counter += 1;
                }

            } else {
                stack.push(char_counter);
            }
            counter += 1;
        }
        if c == Some(']') {
            if result[pointer.0 as usize][pointer.1 as usize] == 1 {
                char_counter = stack.pop().unwrap();
                counter += 1;
                stack.push(char_counter);
            } else {
                stack.pop();
            }
        }
        if pointer.0 == height as u32 {
            pointer.0 = 0;
        }
        if pointer.0 > height as u32 {
            pointer.0 = height as u32 - 1;
        }
        if pointer.1 > width as u32 {
            pointer.1 = width as u32 - 1;
        }
        if pointer.1 == width as u32 {
            pointer.1 = 0;
        }

        char_counter += 1
    }

    let mut tmp = Vec::new();
    for i in 0..height {
        tmp.push(itertools::join(&result[i], ""));
    }
    itertools::join(tmp, "\r\n")
}

#[test]
fn simple_cases() {
    assert_eq!(display_actual(&interpreter("*e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 0, 6, 9)), display_expected("000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000"), "Your interpreter should initialize all cells in the datagrid to 0");
    assert_eq!(display_actual(&interpreter("*e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 7, 6, 9)), display_expected("111100\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000"), "Your interpreter should adhere to the number of iterations specified");
    assert_eq!(display_actual(&interpreter("*e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 19, 6, 9)), display_expected("111100\r\n000010\r\n000001\r\n000010\r\n000100\r\n000000\r\n000000\r\n000000\r\n000000"), "Your interpreter should traverse the 2D datagrid correctly");
    assert_eq!(display_actual(&interpreter("*e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 42, 6, 9)), display_expected("111100\r\n100010\r\n100001\r\n100010\r\n111100\r\n100000\r\n100000\r\n100000\r\n100000"), "Your interpreter should traverse the 2D datagrid correctly for all of the \"n\", \"e\", \"s\" and \"w\" commands");
    assert_eq!(display_actual(&interpreter("*e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 100, 6, 9)), display_expected("111100\r\n100010\r\n100001\r\n100010\r\n111100\r\n100000\r\n100000\r\n100000\r\n100000"), "Your interpreter should terminate normally and return a representation of the final state of the 2D datagrid when all commands have been considered from left to right even if the number of iterations specified have not been fully performed");
    assert_eq!(display_actual(&interpreter("*e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 10, 6, 9)), display_expected("111100\r\n000010\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000\r\n000000"), "Your interpreter should terminate normally and return a representation of the final state of the 2D datagrid when all commands have been considered from left to right even if the number of iterations specified have not been fully performed");
    assert_eq!(display_actual(&interpreter("*e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 15, 8, 8)), display_expected("11110000\r\n00001000\r\n00000100\r\n00000000\r\n00000000\r\n00000000\r\n00000000\r\n00000000"), "Your interpreter should terminate normally and return a representation of the final state of the 2D datagrid when all commands have been considered from left to right even if the number of iterations specified have not been fully performed");
    assert_eq!(display_actual(&interpreter("*e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 25, 10, 10)), display_expected("1111000000\r\n0000100000\r\n0000010000\r\n0000100000\r\n1111000000\r\n0000000000\r\n0000000000\r\n0000000000\r\n0000000000\r\n0000000000"), "Your interpreter should terminate normally and return a representation of the final state of the 2D datagrid when all commands have been considered from left to right even if the number of iterations specified have not been fully performed");
    assert_eq!(display_actual(&interpreter("*e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 50, 16, 9)), display_expected("1111000000000000\r\n1000100000000000\r\n1000010000000000\r\n1000100000000000\r\n1111000000000000\r\n1000000000000000\r\n1000000000000000\r\n1000000000000000\r\n1000000000000000"), "Your interpreter should terminate normally and return a representation of the final state of the 2D datagrid when all commands have been considered from left to right even if the number of iterations specified have not been fully performed");
    assert_eq!(display_actual(&interpreter("*e*e*e*es*es*ws*ws*w*w*w*n*n*n*ssss*s*s*s*", 100, 26, 19)), display_expected("11110000000000000000000000\r\n10001000000000000000000000\r\n10000100000000000000000000\r\n10001000000000000000000000\r\n11110000000000000000000000\r\n10000000000000000000000000\r\n10000000000000000000000000\r\n10000000000000000000000000\r\n10000000000000000000000000\r\n00000000000000000000000000\r\n00000000000000000000000000\r\n00000000000000000000000000\r\n00000000000000000000000000\r\n00000000000000000000000000\r\n00000000000000000000000000\r\n00000000000000000000000000\r\n00000000000000000000000000\r\n00000000000000000000000000\r\n00000000000000000000000000"), "Your interpreter should terminate normally and return a representation of the final state of the 2D datagrid when all commands have been considered from left to right even if the number of iterations specified have not been fully performed");

}