fn chessboard_cell_color(cell1: &str, cell2: &str) -> bool {
    println!("{} {}", cell1, cell2);
    let x1: u32 = cell1.chars().nth(0).unwrap() as u32 - 'A' as u32 + 1;
    let y1: u32 = cell1.chars().nth(1).unwrap().to_digit(10).unwrap();
    let x2: u32 = cell2.chars().nth(0).unwrap() as u32 - 'A' as u32 + 1;
    let y2: u32 = cell2.chars().nth(1).unwrap().to_digit(10).unwrap();
    if (x1 + y1) % 2 == 0 && (x2 + y2) % 2 == 0 {
        return true;
    }
    if (x1 + y1) % 2 == (x2 + y2) % 2 {
        return true;
    }
    false
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn basic_tests() {
        assert_eq!(chessboard_cell_color("A1", "C3"), true);
        assert_eq!(chessboard_cell_color("A1", "H3"), false);
        assert_eq!(chessboard_cell_color("A1", "A2"), false);
        assert_eq!(chessboard_cell_color("A1", "C1"), true);
        assert_eq!(chessboard_cell_color("A1", "A1"), true);
        assert_eq!(chessboard_cell_color("A8", "B3"), true);
        assert_eq!(chessboard_cell_color("C1", "H7"), false);
        assert_eq!(chessboard_cell_color("D3", "F2"), false);
        assert_eq!(chessboard_cell_color("G1", "F6"), true);
        assert_eq!(chessboard_cell_color("F4", "E8"), false);
    }
}