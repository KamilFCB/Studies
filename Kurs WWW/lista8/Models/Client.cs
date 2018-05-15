using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace PoczekalniaApi.Models
{
    public class Client
    {
        public int ID { get; set; }
        public string Imie { get; set; }
        public string Nazwisko { get; set; }
        public string Pesel { get; set; }
    }
}
