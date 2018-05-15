using MvcExample.Models;
using System.Collections.Generic;

namespace MvcExample.Services
{
    public interface IPersonRepository
    {
        IEnumerable<Person> GetAll();
        Person GetById(int id);
    }
    public class PersonRepositoryIM : IPersonRepository
    {
        List<Person> _persons;

        public PersonRepositoryIM()
        {
            _persons = new List<Person>
            {
                new Person { Id = 1, FirstName = "Jan", LastName = "Kowalski", Address = "ul. Trawiasta 10" },
                new Person { Id = 2, FirstName = "Agata", LastName = "Zielony", Address = "ul. Koszykowa 12" },
                new Person { Id = 3, FirstName = "Ewa", LastName = "Szumska", Address = "ul. Zaciszna 3" },
                new Person { Id = 4, FirstName = "Ala", LastName = "Kot", Address = "ul. Cicha 23" },
                new Person { Id = 5, FirstName = "Andrzej", LastName = "Szumski", Address = "ul. Zaciszna 3" },
                new Person { Id = 6, FirstName = "Janusz", LastName = "Nowak", Address = "ul. Kolorowa 73" },
                new Person { Id = 3, FirstName = "Tymoteusz", LastName = "Kowalski", Address = "ul. Morska 83" }
            };
        }
        public IEnumerable<Person> GetAll()
        {
            return _persons;
        }

        public Person GetById(int id)
        {
            foreach (var p in _persons)
                if (p.Id == id)
                    return p;
            return null;
        }
    }
}
