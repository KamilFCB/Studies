using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using PoczekalniaApi.Models;

namespace PoczekalniaApi.Repositories
{
    public interface IVisitsRepository
    {
        List<Visit> FindAll();
        List<Visit> Find(int clientId);
        Visit FindVisit(int id);
        Visit Update(int id, Visit visit);
        Visit Pay(int id);
    }
}
