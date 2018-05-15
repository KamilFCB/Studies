using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;

namespace PoczekalniaApi.Models
{
    public class Visit
    {
        public int ID { get; set; }
        public int ClientID { get; set; }
        public string Data { get; set; }
        public string Godzina { get; set; }
        public string Status { get; set; }
    }
}
