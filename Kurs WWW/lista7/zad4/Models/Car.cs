using System.ComponentModel.DataAnnotations;

namespace FormValidation.Models
{
    public class Car
    {
        public int Id { get; set; }
        [Required(ErrorMessage = "Podaj numer rejestracyjny")]
        [RegularExpression("[A-Z]{2,3}-[0-9]{4,6}", ErrorMessage = "Podany numer rejestracyjny jest niepoprawny")]
        [Display(Name = "Numer rejestracyjny")]
        public string numerRejestracyjny { get; set; }
        [Required(ErrorMessage = "Podaj datę pierwszej rejestracji")]
        //[RegularExpression("[0-9]{2}-[0-9]{2}-[1-2][0-9]{3}", ErrorMessage = "Podana data jest niepoprawna")]
        [Display(Name = "Data rejestracji")]
        public string dataRejestracji { get; set; }
        [Required(ErrorMessage = "Podaj marke samochodu")]
        [RegularExpression("[A-Z][a-z]+", ErrorMessage = "Podana marka jest niepoprawna")]
        [Display(Name = "Marka")]
        public string Marka { get; set; }
        [Required(ErrorMessage = "Podaj rok produkcji")]
        [RegularExpression("[1-2]{1}[0-9]{3}", ErrorMessage = "Podany rok produkcji jest niepoprawny")]
        [Display(Name = "Rok produkcji")]
        public string rokProdukcji { get; set; }
        [Required(ErrorMessage = "Podaj paliwo(P, LPG, ON, EE")]
        [RegularExpression("P|LPG|ON|EE", ErrorMessage = "Podane paliwo jest niepoprawne")]
        [Display(Name = "Paliwo")]
        public string Paliwo { get; set; }
    }
}
