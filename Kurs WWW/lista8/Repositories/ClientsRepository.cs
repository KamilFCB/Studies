using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using PoczekalniaApi.Models;

namespace PoczekalniaApi.Repositories
{
    public class ClientsRepository : IClientsRepository
    {
        private List<Client> Clients = new List<Client>
        {
            new Client {ID = 1, Imie = "Kamil", Nazwisko = "Woś", Pesel = "12345678910"},
            new Client {ID = 2, Imie = "Andrzej", Nazwisko = "Kowalski", Pesel = "12345678911"}
        };

        public List<Client> FindAll()
        {
            return Clients;
        }

        public Client Find(int id)
        {
            return Clients.Find(e => e.ID == id);
        }

        public Client Update(int id, Client client)
        {
            var c = Clients.Find(e => e.ID == id);
            if (c != null)
            {
                if (!string.IsNullOrEmpty(c.Imie))
                    c.Imie = client.Imie;
                if (!string.IsNullOrEmpty(c.Nazwisko))
                    c.Nazwisko = client.Nazwisko;
                if (!string.IsNullOrEmpty(c.Pesel))
                    c.Pesel = client.Pesel;
            }

            return c;
        }
    }
}
