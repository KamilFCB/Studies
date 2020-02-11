fn dna_strand(dna: &str) -> String {
    dna.chars().into_iter().map(|ch|
        match ch {
            'T' => 'A',
            'A' => 'T',
            'G' => 'C',
            'C' => 'G',
            _ => ch
        }
    ).collect::<String>()
}

#[cfg(test)]
mod tests {
    use super::dna_strand;

    #[test]
    fn returns_expected() {
        assert_eq!(dna_strand("AAAA"),"TTTT");
        assert_eq!(dna_strand("ATTGC"),"TAACG");
        assert_eq!(dna_strand("GTAT"),"CATA");
        assert_eq!(dna_strand("ATGATAGC"),"TACTATCG");
        assert_eq!(dna_strand("GGTACTA"),"CCATGAT");
        assert_eq!(dna_strand("GATTAGA"),"CTAATCT");
        assert_eq!(dna_strand("AGATA"),"TCTAT");
        assert_eq!(dna_strand("CAGTA"),"GTCAT");
        assert_eq!(dna_strand("GGGATATATGCCAT"),"CCCTATATACGGTA");
        assert_eq!(dna_strand("CCTTAGACTCTCAA"),"GGAATCTGAGAGTT");
    }
}