use std::collections::HashSet;

struct Sudoku{
    data: Vec<Vec<u32>>,
}


impl Sudoku{
    fn valid_rows(&self, sudoku_size: usize) -> bool {
        for row in 0..sudoku_size {
            if self.data[row].len() != sudoku_size {
                return false;
            }
            let mut number_set = HashSet::new();
            for column in 0..sudoku_size {
                let v: u32 = self.data[row][column];
                if v == 0 || v > (sudoku_size as u32) {
                    return false;
                }
                if !number_set.insert(v) {
                    return false;
                }
            }
        }
        true
    }

    fn valid_columns(&self, sudoku_size: usize) -> bool {
        if self.data.len() != sudoku_size {
            return false;
        }
        for column in 0..sudoku_size {
            for row in 0..sudoku_size {
                let mut number_set = HashSet::new();
                let v: u32 = self.data[row][column];
                if v == 0 || v > (sudoku_size as u32) {
                    return false;
                }
                if !number_set.insert(v) {
                    return false;
                }
            }
        }
        true
    }

    fn valid_boxes(&self, box_size: usize) -> bool {
        for i in 0..box_size {
            let mut number_set = HashSet::new();
            for j in 0..box_size {
                for k in 0..box_size {
                    let v: u32 = self.data[(i * box_size) + j][(i * box_size) + k];
                    if !number_set.insert(v) {
                        return false;
                    }
                }
            }
        }
        true
    }

    fn is_valid(&self) -> bool {
        let size = self.data.len();
        let box_size = (size as f32).sqrt() as usize;

        Self::valid_rows(self, size) && Self::valid_columns(self, size) && Self::valid_boxes(self, box_size)
    }
}

#[test]
fn good_sudoku() {
    let good_sudoku_1 = Sudoku{
        data: vec![
            vec![7,8,4, 1,5,9, 3,2,6],
            vec![5,3,9, 6,7,2, 8,4,1],
            vec![6,1,2, 4,3,8, 7,5,9],

            vec![9,2,8, 7,1,5, 4,6,3],
            vec![3,5,7, 8,4,6, 1,9,2],
            vec![4,6,1, 9,2,3, 5,8,7],

            vec![8,7,6, 3,9,4, 2,1,5],
            vec![2,4,3, 5,6,1, 9,7,8],
            vec![1,9,5, 2,8,7, 6,3,4]
        ]
    };

    let good_sudoku_2 = Sudoku{
        data: vec![
            vec![1, 4,  2, 3],
            vec![3, 2,  4, 1],

            vec![4, 1,  3, 2],
            vec![2, 3,  1, 4],
        ]
    };
    assert!(good_sudoku_1.is_valid());
    assert!(good_sudoku_2.is_valid());
}

#[test]
fn bad_sudoku() {
    let bad_sudoku_1 = Sudoku{
        data: vec![
            vec![1,2,3, 4,5,6, 7,8,9],
            vec![1,2,3, 4,5,6, 7,8,9],
            vec![1,2,3, 4,5,6, 7,8,9],

            vec![1,2,3, 4,5,6, 7,8,9],
            vec![1,2,3, 4,5,6, 7,8,9],
            vec![1,2,3, 4,5,6, 7,8,9],

            vec![1,2,3, 4,5,6, 7,8,9],
            vec![1,2,3, 4,5,6, 7,8,9],
            vec![1,2,3, 4,5,6, 7,8,9],
        ]
    };

    let bad_sudoku_2 = Sudoku{
        data: vec![
            vec![1,2,3,4,5],
            vec![1,2,3,4],
            vec![1,2,3,4],
            vec![1],
        ]
    };
    assert!(!bad_sudoku_1.is_valid());
    assert!(!bad_sudoku_2.is_valid());
}