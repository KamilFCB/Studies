using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using PoczekalniaApi.Models;
using System.Collections.Generic;

namespace PoczekalniaApi.Repositories
{
    public interface IClientsRepository
    {
        List<Client> FindAll();
        Client Find(int id);
        Client Update(int id, Client client);
    }
}
